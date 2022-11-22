#ifndef COOKTORRANCESHADER_H
#define COOKTORRANCESHADER_H

#include "ShaderSupport.h"
#include "PixelBuffer.h"

class CookTorranceShader : public Shader
{

private:

    const Vector4& lightPosition;
    const PixelBuffer& albedo;
    const PixelBuffer& roughness;
    const PixelBuffer& ao;
    const PixelBuffer& normalMap;
    //const Matrix4x4& tangentToView;

    static const Vector4 AMBIENT_COLOR;

public:

    CookTorranceShader(const Vector4& lightPosition, const PixelBuffer& albedo, const PixelBuffer& roughness, const PixelBuffer& ao, const PixelBuffer& normalMap);

    Vector4 execute(const Vertex& vert) const override;

};


#endif /* COOKTORRANCE_SHADER_H */
