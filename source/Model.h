#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Vector4.h"

class Model
{

private:

    void loadModel(const std::string& filename);

    std::vector<Vector4> verts;
    std::vector<Vector4> normals;
    std::vector<Vector4> uvs;
    std::vector<Vector4> tangents;
    std::vector<Vector4> bitangents;
    std::vector<int> indices;
    std::vector<int> normalIndices;
    std::vector<int> uvIndices;

public:


    // loads from fileName
    Model(const std::string& fileName);

    const std::vector<Vector4>& getVerts() const;
    const std::vector<Vector4>& getNormals() const;
    const std::vector<Vector4>& getUVs() const;
    const std::vector<Vector4>& getTangents() const;
    const std::vector<Vector4>& getBitangents() const;
    const std::vector<int>& getIndices() const;
    const std::vector<int>& getNormalIndices() const;
    const std::vector<int>& getUVIndices() const;
};

#endif /* MODEL_H */
