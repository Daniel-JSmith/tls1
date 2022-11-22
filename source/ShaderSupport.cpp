#include "ShaderSupport.h"
#include "CoordinateSystems.h"

Vector4 Shader::operator()(const Vertex& vert) const
{
    return execute(vert);
}

float ShaderSupport::clampedLambert(const Vector4& normal, const Vector4& light)
{
    return std::max(0.0f, light.dot(normal));
}

Vector4 ShaderSupport::reflectionDirection(const Vector4& normal, const Vector4& in)
{
    return -in + normal * (2 * in.dot(normal));
}

Vector4 ShaderSupport::sampleTexture(const PixelBuffer& texture, float u, float v)
{
    Vector4 uv = CoordinateSystems::screenToDevice(Vector4(u, v, 0, 0), texture.getWidth(), texture.getHeight());
    return texture.getPixel(uv.x, uv.y);
}
