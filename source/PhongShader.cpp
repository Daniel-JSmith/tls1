#include "PhongShader.h"

#include <cmath>

const Vector4 PhongShader::AMBIENT_COLOR{0.75f, 0.5f, 0.5f, 1.0f};
const float PhongShader::AMBIENT_CONSTANT{0.25f};
const float PhongShader::SPECULAR_CONSTANT{0.5f};
const int PhongShader::SPECULAR_POWER{8};

PhongShader::PhongShader(const Vector4& lightPosition) : lightPosition(lightPosition)
{
}

Vector4 PhongShader::execute(const Vertex& vert) const
{
    auto viewDirection = -vert.eyePosition;
    viewDirection.w = 0.0f;
    viewDirection = viewDirection.normalized();

    auto lightDirection = (lightPosition - vert.eyePosition);
    lightDirection.w = 0.0f;
    lightDirection = lightDirection.normalized();

    auto normal = vert.normal.normalized();

    auto reflectionDirection = ShaderSupport::reflectionDirection(normal, lightDirection);
    reflectionDirection.w = 0.0f;
    reflectionDirection = reflectionDirection.normalized();

    auto lambert = ShaderSupport::clampedLambert(normal, lightDirection);

    auto diffuse = AMBIENT_COLOR * (lambert * (1 - AMBIENT_CONSTANT) + AMBIENT_CONSTANT);
    auto specular = Vector4(1,1,1,1) * (SPECULAR_CONSTANT * pow(std::max(0.0f, viewDirection.dot(reflectionDirection)), SPECULAR_POWER));

    auto out = diffuse + specular;
    return out;
}
