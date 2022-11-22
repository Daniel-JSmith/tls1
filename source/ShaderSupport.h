#ifndef SHADER_H
#define SHADER_H

#include "Vertex.h"
#include "PixelBuffer.h"

class Shader
{
private:

public:

    Shader() = default;
    Shader(const Shader&) = default;
    Shader(Shader&&) = default;

    Shader& operator=(const Shader&) = default;
    Shader& operator=(Shader&&) = default;

    virtual Vector4 execute(const Vertex&) const = 0;

    Vector4 operator()(const Vertex&) const;

    virtual ~Shader() = default;
};

// Assume all vectors pointing away from surface
namespace ShaderSupport
{
    const float EULER = 2.718f;

    // Assumes arguments normalized
    float clampedLambert(const Vector4& normal, const Vector4& light);

    Vector4 reflectionDirection(const Vector4& normal, const Vector4& in);

    // cheap hack to ensure color doesn't overflow. Should be handled in Color
    // class, but there's a bug there. I'll remove this code once it's working
    void clampColor(Vector4& color);

    // Takes u,v coordinates ([0,1])
    Vector4 sampleTexture(const PixelBuffer& texture, float u, float v);
}

#endif /* SHADER_H */
