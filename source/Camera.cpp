#include "Camera.h"

#include <math.h>

#include "CoordinateSystems.h"

Camera::Camera(float horizontalFOV, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
    : halfHorizontalFOV((horizontalFOV / 2.0f) * (M_PI / 180.0f)),
      aspectRatio(aspectRatio),
      nearPlaneDistance(nearPlaneDistance),
      farPlaneDistance(farPlaneDistance)
{
}
    
Camera::Camera() : Camera(90, 1.0f, 1.0f, 10.0f)
{
}

void Camera::getV(Matrix4x4& result) const
{
    transform.getInverseTR(result);
}

void Camera::getP(Matrix4x4& result) const
{
    result = CoordinateSystems::getProjectionMatrix(halfHorizontalFOV, aspectRatio, nearPlaneDistance, farPlaneDistance);
}

Transform& Camera::getTransform()
{
    return const_cast<Transform&>(static_cast<const Camera&>(*this).getTransform());
}

const Transform& Camera::getTransform() const
{
    return transform;
}

