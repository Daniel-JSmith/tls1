#include "LambertShader.h"

LambertShader::LambertShader(const Vector4& lightPosition, const PixelBuffer& texture) : lightPosition(lightPosition), texture(texture)
{
}

Vector4 LambertShader::execute(const Vertex& vert) const
{
    auto lightDirection = (lightPosition - vert.eyePosition).normalized();
    auto lambert = ShaderSupport::clampedLambert(vert.normal.normalized(), lightDirection);

    auto texColor = ShaderSupport::sampleTexture(texture, vert.uv.x, vert.uv.y);

    return texColor * lambert;
}

