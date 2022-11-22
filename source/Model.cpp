#include "Model.h"

#include <fstream>
#include <sstream>

#include <iostream>

void Model::loadModel(const std::string& filename)
{
    std::ifstream file;
    file.open(filename);
    if (file.fail())
    {
        throw std::runtime_error("couldn't open file: " + filename);
    }

    std::string line;
    while(getline(file, line))
    {
        std::stringstream lineStream(line);

        std::string firstToken;
        lineStream >> firstToken;

        if (firstToken == "v")
        {
            float x, y, z;
            lineStream >> x >> y >> z;
            verts.emplace_back(x, y, z, 1);
        }
        else if (firstToken == "vt")
        {
            float u, v;
            lineStream >> u >> v;
            uvs.emplace_back(u, v, 0, 0);
        }
        else if (firstToken == "vn")
        {
            float x, y, z;
            lineStream >> x >> y >> z;
            normals.emplace_back(x, y, z, 0);
        }
        else if (firstToken == "f")
        {
            for (int i = 0; i < 3; i++)
            {
                auto face = std::string();
                lineStream >> face;

                auto delimiterPos0 = face.find('/');
                auto delimiterPos1 = face.find('/', delimiterPos0 + 1);
                auto posIndex = face.substr(0, delimiterPos0);
                auto uvIndex = face.substr(delimiterPos0 + 1, delimiterPos1 - delimiterPos0 - 1);
                auto normalIndex = face.substr(delimiterPos1 + 1);

                indices.push_back(std::stoi(posIndex));
                uvIndices.push_back(std::stoi(uvIndex));
                normalIndices.push_back(std::stoi(normalIndex));
            }
        }
    }

    file.close();


    for(int i = 0; i < indices.size() - 2; i += 3)
    {
        int index0 = indices.at(i) - 1;
        int index1 = indices.at(i + 1) - 1;
        int index2 = indices.at(i + 2) - 1;
        Vector4 vert0 = verts.at(index0);
        Vector4 vert1 = verts.at(index1);
        Vector4 vert2 = verts.at(index2);

        int uvIndex0 = uvIndices.at(i) - 1;
        int uvIndex1 = uvIndices.at(i + 1) - 1;
        int uvIndex2 = uvIndices.at(i + 2) - 1;
        Vector4 uv0 = uvs.at(uvIndex0);
        Vector4 uv1 = uvs.at(uvIndex1);
        Vector4 uv2 = uvs.at(uvIndex2);

        auto edge0Position = vert1 - vert0;
        auto edge1Position = vert2 - vert0;
        auto edge0UV = uv1 - uv0;
        auto edge1UV = uv2 - uv0;

        edge0Position = vert2 - vert0;
        edge1Position = vert1 - vert0;
        edge0UV = uv2 - uv0;
        edge1UV = uv1 - uv0;

        auto denominator = 1.0f / (edge0UV.x * edge1UV.y - edge1UV.x * edge0UV.y);
        auto tangentX = denominator * (edge1UV.y * edge0Position.x - edge0UV.y * edge1Position.x);
        auto tangentY = denominator * (edge1UV.y * edge0Position.y - edge0UV.y * edge1Position.y);
        auto tangentZ = denominator * (edge1UV.y * edge0Position.z - edge0UV.y * edge1Position.z);
        auto bitangentX = denominator * (-edge1UV.x * edge0Position.x + edge0UV.x * edge1Position.x);
        auto bitangentY = denominator * (-edge1UV.x * edge0Position.y + edge0UV.x * edge1Position.y);
        auto bitangentZ = denominator * (-edge1UV.x * edge0Position.z + edge0UV.x * edge1Position.z);
        tangents.emplace_back(tangentX, tangentY, tangentZ, 0);
        bitangents.emplace_back(bitangentX, bitangentY, bitangentZ, 0);

        /*
        auto denominator = 1.0f / (edge0UV.x * edge1UV.y - edge1UV.x * edge0UV.y);
        auto tangent = (edge0Position * edge1UV.y - edge1Position * edge1UV.y) * denominator;
        auto bitangent = (edge1Position * edge0UV.x - edge0Position * edge1UV.x) * denominator;

        tangents.push_back(tangent);
        bitangents.push_back(bitangent);
        */
    }
}

Model::Model(const std::string& filename)
{
    loadModel(filename);
}

const std::vector<Vector4>& Model::getVerts() const
{
    return verts;
}

const std::vector<Vector4>& Model::getNormals() const
{
    return normals;
}

const std::vector<Vector4>& Model::getUVs() const
{
    return uvs;
}

const std::vector<Vector4>& Model::getTangents() const
{
    return tangents;
}

const std::vector<Vector4>& Model::getBitangents() const
{
    return bitangents;
}

const std::vector<int>& Model::getIndices() const
{
    return indices;
}

const std::vector<int>& Model::getNormalIndices() const
{
    return normalIndices;
}

const std::vector<int>& Model::getUVIndices() const
{
    return uvIndices;
}

