#include "CookTorranceShader.h"

#include <cmath>

const Vector4 CookTorranceShader::AMBIENT_COLOR{0.25f, 0.125f, 0.125f, 1.0f};

CookTorranceShader::CookTorranceShader(const Vector4& lightPosition, const PixelBuffer& albedo, const PixelBuffer& roughness, const PixelBuffer& ao, const PixelBuffer& normalMap) : lightPosition(lightPosition),
           albedo(albedo),
           roughness(roughness),
           ao(ao),
           normalMap(normalMap)
{
}

namespace{

    float fresnel(const Vector4& V, const Vector4& H)
    {
        static auto const F0 = 0.4f;
        return F0 + (1 - F0) * pow(1 - V.dot(H), 5);
    }

    float reflectanceDistributionBeckmann(const Vector4& N, const Vector4& H, float roughness)
    {
        auto tanAlpha = tan(acos(N.dot(H)));
        auto exponent = -pow(tanAlpha / roughness, 2);
        auto numerator = pow(ShaderSupport::EULER, exponent);
        auto denominator = roughness * roughness * pow(N.dot(H), 4);
        return numerator / denominator;
    }

    float reflactanceDistributionGaussian(const Vector4& N, const Vector4& H, float roughness)
    {
        static auto const C = 1.0f;
        auto alpha = acos(N.dot(H));
        return C * pow(ShaderSupport::EULER, -pow(alpha / roughness, 2));
    }

    float attenuationFactor(const Vector4& L, const Vector4& N, const Vector4& V, const Vector4& H)
    {
        auto inputA = 2 * N.dot(H) * N.dot(V) / V.dot(H);
        auto inputB = 2 * N.dot(H) * N.dot(L) / V.dot(H);
        return std::min(std::min(inputA, inputB), 1.0f);
    }
}

Vector4 CookTorranceShader::execute(const Vertex& vert) const
{
    auto viewDirection = -vert.eyePosition;
    viewDirection.w = 0.0f;
    viewDirection = viewDirection.normalized();

    Vector4 albedoSample = ShaderSupport::sampleTexture(albedo, vert.uv.x, vert.uv.y);
    Vector4 roughnessSample = ShaderSupport::sampleTexture(roughness, vert.uv.x, vert.uv.y);
    Vector4 aoSample = ShaderSupport::sampleTexture(ao, vert.uv.x, vert.uv.y);
    auto ambient = Vector4(AMBIENT_COLOR.x * aoSample.x, AMBIENT_COLOR.y * aoSample.y, AMBIENT_COLOR.z * aoSample.z, 1);

    auto lightDirection = (lightPosition - vert.eyePosition).normalized();
    lightDirection.w = 0.0f;

    auto normal = vert.normal.normalized();

    auto H = (viewDirection + lightDirection).normalized();
    auto F = fresnel(viewDirection, H);
    auto D = reflectanceDistributionBeckmann(normal, H, roughnessSample.x);
    auto G = attenuationFactor(lightDirection, normal, viewDirection, H);

    auto Ks = F * D * G / (4 * normal.dot(lightDirection) * normal.dot(viewDirection));
    auto Kd = 1 - Ks;

    auto direct = std::max(0.0f, normal.dot(lightDirection)) * (albedoSample * Kd + Vector4(1,1,1,1) * Ks);
    
    auto out = ambient + direct;

    return out;
}

