#ifndef LAMBERTSHADER_H
#define LAMBERTSHADER_H

#include "ShaderSupport.h"

#include "PixelBuffer.h"


class LambertShader : public Shader
{

private:

    const Vector4& lightPosition;
    const PixelBuffer& texture;

public:

    LambertShader(const Vector4& lightPosition, const PixelBuffer& texture);
    Vector4 execute(const Vertex& vert) const override;

};

#endif /* LAMBERTSHADER_H */
