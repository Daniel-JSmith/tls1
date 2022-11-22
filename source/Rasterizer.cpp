#include <iostream>
#include <functional>

#include "Rasterizer.h"

#include "CoordinateSystems.h"
#include "Quaternion.h"
#include "LambertShader.h"
#include "PhongShader.h"
#include "CookTorranceShader.h"

#include <cmath>
#include <limits>


float crossZMag(const Vector4& vec0, const Vector4& vec1)
{
    return (vec0.x * vec1.y) - (vec0.y * vec1.x);
}

inline float crossZMag(float x0, float y0, float x1, float y1)
{
    return (x0 * y1) - (y0 * x1);
}

float constexpr edgeTestEpsilon()
{
    return std::numeric_limits<float>::epsilon() * 10;
    //return 0;
}

template <typename T>
bool inline edgeTestExclusive(T BC)
{
    return BC >= -edgeTestEpsilon();
}

template <typename T>
bool inline edgeTestInclusive(T BC)
{
    return BC >= -edgeTestEpsilon();
}

void getInterpolationCoefficients(const Vector4& start, const Vector4& end, float doubleTriangleArea, float& constant, float& xIncrement, float& yIncrement)
{
    constant = (end.x * start.y - end.y * start.x) / doubleTriangleArea;
    xIncrement = (end.y - start.y) / doubleTriangleArea;
    yIncrement = (start.x - end.x) / doubleTriangleArea;
}

void drawTriangleBary(const Vertex& vert0, const Vertex& vert1, const Vertex& vert2, const Shader& shader, PixelBuffer& target)
{
    auto lowX = std::min(std::min(vert0.position.x, vert1.position.x), vert2.position.x);
    auto highX = std::max(std::max(vert0.position.x, vert1.position.x), vert2.position.x);
    auto lowY = std::min(std::min(vert0.position.y, vert1.position.y), vert2.position.y);
    auto highY = std::max(std::max(vert0.position.y, vert1.position.y), vert2.position.y);

    auto triangleArea2 = crossZMag(vert1.position - vert0.position, vert2.position - vert0.position);

    float BC0Constant, BC0XIncrement, BC0YIncrement;
    getInterpolationCoefficients(vert0.position, vert2.position, triangleArea2, BC0Constant, BC0XIncrement, BC0YIncrement);
    float BC1Constant, BC1XIncrement, BC1YIncrement;
    getInterpolationCoefficients(vert1.position, vert0.position, triangleArea2, BC1Constant, BC1XIncrement, BC1YIncrement);
    float BC2Constant, BC2XIncrement, BC2YIncrement;
    getInterpolationCoefficients(vert2.position, vert1.position, triangleArea2, BC2Constant, BC2XIncrement, BC2YIncrement);

    float x = floor(lowX) + 0.5f;
    float y = floor(lowY) + 0.5f;

    auto BC0 = x * BC0XIncrement + y * BC0YIncrement + BC0Constant;
    auto BC1 = x * BC1XIncrement + y * BC1YIncrement + BC1Constant;
    auto BC2 = x * BC2XIncrement + y * BC2YIncrement + BC2Constant;

    auto edgeTest0 = vert2.position.y < vert0.position.y ? edgeTestExclusive<decltype(BC0)> : edgeTestInclusive<decltype(BC0)>;
    auto edgeTest1 = vert0.position.y < vert1.position.y ? edgeTestExclusive<decltype(BC0)> : edgeTestInclusive<decltype(BC0)>;
    auto edgeTest2 = vert1.position.y < vert2.position.y ? edgeTestExclusive<decltype(BC0)> : edgeTestInclusive<decltype(BC0)>;

    auto vert0Attributes = vert0.getAttributes();
    auto vert1Attributes = vert1.getAttributes();
    auto vert2Attributes = vert2.getAttributes();
    auto interpolatedVert = vert0;
    auto interpolantXIncrements = vert0.getAttributes();
    auto interpolantYIncrements = vert0.getAttributes();

    for (int i = 0; i < vert0Attributes.size(); i++)
    {
        interpolatedVert[i] = (vert1Attributes.at(i) * BC0 * vert1.position.w) + (vert2Attributes.at(i) * BC1 * vert2.position.w) + (vert0Attributes.at(i) * BC2 * vert0.position.w);
        interpolantXIncrements.at(i) = (vert1Attributes.at(i) * BC0XIncrement * vert1.position.w) + (vert2Attributes.at(i) * BC1XIncrement * vert2.position.w) + (vert0Attributes.at(i) * BC2XIncrement * vert0.position.w);
        interpolantYIncrements.at(i) = (vert1Attributes.at(i) * BC0YIncrement * vert1.position.w) + (vert2Attributes.at(i) * BC1YIncrement * vert2.position.w) + (vert0Attributes.at(i) * BC2YIncrement * vert0.position.w);
    }

    auto w = (vert1.position.w * BC0) + (vert2.position.w * BC1) + (vert0.position.w * BC2);
    auto wXIncrement = (vert1.position.w * BC0XIncrement) + (vert2.position.w * BC1XIncrement) + (vert0.position.w * BC2XIncrement);
    auto wYIncrement = (vert1.position.w * BC0YIncrement) + (vert2.position.w * BC1YIncrement) + (vert0.position.w * BC2YIncrement);

    auto xDirection = 1;
    std::function<bool(decltype(x))> boundCheck = [highX](auto x) { return x <= highX; };
    std::function<bool(decltype(x))> reverseBoundCheck = [lowX](auto x) { return x >= lowX; };

    for (; y <= highY; y++)
    {
        for (; boundCheck(x); x += xDirection)
        {
            auto shadingVert = interpolatedVert;
            for (int i = 0; i < vert0Attributes.size(); i++)
            {
                shadingVert[i] /= w;
            }

            if (edgeTest0(BC0) && edgeTest1(BC1) && edgeTest2(BC2))
            {
                target.setPixelWithDepthTest(x, y, shadingVert.position.z, shader.execute(shadingVert));
            }

            BC0 += BC0XIncrement * xDirection;
            BC1 += BC1XIncrement * xDirection;
            BC2 += BC2XIncrement * xDirection;

            for (int i = 0; i < vert0Attributes.size(); i++)
            {
                interpolatedVert[i] += interpolantXIncrements.at(i) * xDirection;
            }

            w += wXIncrement * xDirection;
        }

        swap(boundCheck, reverseBoundCheck);
        xDirection = -xDirection;

        BC0 += BC0YIncrement;
        BC1 += BC1YIncrement;
        BC2 += BC2YIncrement;

        for (int i = 0; i < vert0Attributes.size(); i++)
        {
            interpolatedVert[i] += interpolantYIncrements.at(i);
        }

        w += wYIncrement;
    }
}

void Rasterizer::draw(Vertex& vertex0,
                          Vertex& vertex1,
                          Vertex& vertex2,
                          const Shader& shader,
                          PixelBuffer& target)
{
    if (!CoordinateSystems::withinClipVolume(vertex0.position) || !CoordinateSystems::withinClipVolume(vertex1.position) || !CoordinateSystems::withinClipVolume(vertex2.position))
    {
        return;
    }

    vertex0.position = CoordinateSystems::screenToDevice(CoordinateSystems::NDCToScreen(CoordinateSystems::clipToNDC(vertex0.position)), target.getWidth(), target.getHeight());
    vertex1.position = CoordinateSystems::screenToDevice(CoordinateSystems::NDCToScreen(CoordinateSystems::clipToNDC(vertex1.position)), target.getWidth(), target.getHeight());
    vertex2.position = CoordinateSystems::screenToDevice(CoordinateSystems::NDCToScreen(CoordinateSystems::clipToNDC(vertex2.position)), target.getWidth(), target.getHeight());

    //vertex0.uv = CoordinateSystems::screenToDevice(vertex0.uv, texture.getWidth(), texture.getHeight());
    //vertex1.uv = CoordinateSystems::screenToDevice(vertex1.uv, texture.getWidth(), texture.getHeight());
    //vertex2.uv = CoordinateSystems::screenToDevice(vertex2.uv, texture.getWidth(), texture.getHeight());

    auto geometryNormal = (vertex1.position - vertex0.position).cross(vertex2.position - vertex0.position);
    // back facing
    if (geometryNormal.dot(Vector4(0, 0, 1, 0)) < -std::numeric_limits<float>::epsilon())
    {
        return;
    }

    drawTriangleBary(vertex0, vertex1, vertex2, shader, target);
}

