#include "CoordinateSystems.h"
#include <cmath>

bool CoordinateSystems::withinClipVolume(const Vector4& vert)
{
    return vert.x > -vert.w && vert.x < vert.w
        && vert.y > -vert.w && vert.y < vert.w
        && vert.z > 0 && vert.z < vert.w;
}

Vector4 CoordinateSystems::clipToNDC(const Vector4& clip)
{
    return Vector4(clip.x / clip.w, clip.y / clip.w, clip.z / clip.w, 1 / clip.w);
}

float inline toScreen(float in)
{
    return in / 2.0f + 0.5f;
}

Vector4 CoordinateSystems::NDCToScreen(const Vector4& NDC)
{
    return Vector4(toScreen(NDC.x), toScreen(NDC.y), NDC.z, NDC.w);
}

int inline continuousToDiscrete(float continuous)
{
    return static_cast<int>(round(continuous));
}

Vector4 CoordinateSystems::screenToDevice(const Vector4& screen, int deviceWidth, int deviceHeight)
{
    /*
    return Vector4(continuousToDiscrete(screen.x * deviceWidth)
                 , continuousToDiscrete(screen.y * deviceHeight)
                 , screen.z
                 , screen.w);
    */

    return Vector4(screen.x * deviceWidth
                 , screen.y * deviceHeight
                 , screen.z
                 , screen.w);
 
}

Matrix4x4 CoordinateSystems::getProjectionMatrix(float halfHorizontalFOV, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
{
    float x = tan(M_PI_2 - halfHorizontalFOV);
    float y = x * aspectRatio;
    float zA = - farPlaneDistance / (farPlaneDistance - nearPlaneDistance);
    float zB = - nearPlaneDistance * farPlaneDistance / (farPlaneDistance - nearPlaneDistance);
    return Matrix4x4(Vector4(x, 0, 0, 0),
                       Vector4(0, y, 0, 0),
                       Vector4(0, 0, zA, zB),
                       Vector4(0, 0, -1, 0));
}

Vector4 CoordinateSystems::worldToViewSpace(const Vector4& vec, const Camera& view)
{
    Matrix4x4 viewMat;
    view.getV(viewMat);
    return viewMat * vec;
}

