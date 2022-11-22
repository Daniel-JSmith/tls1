#include "Rendering.h"
#include "Rasterizer.h"

void Rendering::draw(const Drawable& drawable, const Camera& camera, const Shader& shader, PixelBuffer& target)
{
    const std::vector<Vector4>& verts = drawable.getModel().getVerts();
    const std::vector<Vector4>& normals = drawable.getModel().getNormals();
    const std::vector<Vector4>& uvs = drawable.getModel().getUVs();
    const std::vector<Vector4>& tangents = drawable.getModel().getTangents();
    const std::vector<Vector4>& bitangents = drawable.getModel().getBitangents();
    const std::vector<int>& indices = drawable.getModel().getIndices();
    const std::vector<int>& normalIndices = drawable.getModel().getNormalIndices();
    const std::vector<int>& uvIndices = drawable.getModel().getUVIndices();
    
    for(int i = 0; i < indices.size() - 2; i += 3)
    {
        int index0 = indices.at(i) - 1;
        int index1 = indices.at(i + 1) - 1;
        int index2 = indices.at(i + 2) - 1;
        Vector4 vert0 = verts.at(index0);
        Vector4 vert1 = verts.at(index1);
        Vector4 vert2 = verts.at(index2);

        int nIndex0 = normalIndices.at(i) - 1;
        int nIndex1 = normalIndices.at(i + 1) - 1;
        int nIndex2 = normalIndices.at(i + 2) - 1;
        Vector4 n0 = normals.at(nIndex0);
        Vector4 n1 = normals.at(nIndex1);
        Vector4 n2 = normals.at(nIndex2);

        int uvIndex0 = uvIndices.at(i) - 1;
        int uvIndex1 = uvIndices.at(i + 1) - 1;
        int uvIndex2 = uvIndices.at(i + 2) - 1;
        Vector4 uv0 = uvs.at(uvIndex0);
        Vector4 uv1 = uvs.at(uvIndex1);
        Vector4 uv2 = uvs.at(uvIndex2);


        // model
        Matrix4x4 modelMat;
        drawable.getTransform().getTRS(modelMat);
        Matrix4x4 viewMat;
        camera.getV(viewMat);
        Matrix4x4 projectionMat;
        camera.getP(projectionMat);
        Matrix4x4 MV = viewMat * modelMat;
        Matrix4x4 MVP = projectionMat * MV;

        Vector4 eye0 = MV * vert0;
        Vector4 eye1 = MV * vert1;
        Vector4 eye2 = MV * vert2;

        auto transposedCameraRotation = camera.getTransform().getRotationMatrix();
        transposedCameraRotation.transpose();
        auto modelRotation = drawable.getTransform().getRotationMatrix();
        auto inverseModelScale = drawable.getTransform().getScaleMatrix();
        inverseModelScale.invertMainDiagonal();

        auto normalMat = transposedCameraRotation * modelRotation * inverseModelScale;


        //auto tbnNormal = modelMat * tangent.cross(bitangent);
        //auto tangent = modelMat * tangents.at(i / 3);
        //auto bitangent =  modelMat * bitangents.at(i / 3);
        //auto tbnNormal =  modelMat * (vert2 - vert0).cross(vert1 - vert0);

        auto tangent = MV * tangents.at(i / 3);
        auto bitangent =  MV * bitangents.at(i / 3);
        auto tbnNormal =  MV * (vert2 - vert0).cross(vert1 - vert0);

        tangent = tangent.normalized();
        bitangent = bitangent.normalized();
        tbnNormal = tbnNormal.normalized();

        if (tbnNormal.cross(tangent).dot(bitangent) < 0.0f)
        {
            tangent = -tangent;
        }

        Matrix4x4 TBN(Vector4(tangent.x, bitangent.x, tbnNormal.x, 0),
                      Vector4(tangent.y, bitangent.y, tbnNormal.y, 0),
                      Vector4(tangent.z, bitangent.x, tbnNormal.z, 0),
                      Vector4(        0,           0,        0, 1)
                );
        //Matrix4x4 TBN(tangent, bitangent, tbnNormal, Vector4(0, 0, 0, 1));

        vert0 = MVP * vert0;
        vert1 = MVP * vert1;
        vert2 = MVP * vert2;


        n0 = normalMat * n0;
        n1 = normalMat * n1;
        n2 = normalMat * n2;




        Vertex v0(vert0, n0, uv0, eye0);
        Vertex v1(vert1, n1, uv1, eye1);
        Vertex v2(vert2, n2, uv2, eye2);

        Rasterizer::draw(v0, v1, v2, shader, target);
    }
}

