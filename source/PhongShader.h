#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "ShaderSupport.h"

class PhongShader : public Shader
{

private:

    const Vector4& lightPosition;

    static const Vector4 AMBIENT_COLOR;
    static const float AMBIENT_CONSTANT;
    static const float SPECULAR_CONSTANT;
    static const int SPECULAR_POWER;

public:

    PhongShader(const Vector4& lightPosition);

    Vector4 execute(const Vertex& vert) const override;

};

#endif /* PHONGSHADER_H */
