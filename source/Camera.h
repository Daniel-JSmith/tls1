#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"

class Camera
{

private:

    Transform transform;

    // radians
    float halfHorizontalFOV;
    float aspectRatio;

    // distance from camera in view or world space
    float nearPlaneDistance;
    float farPlaneDistance;

public:

    // FOV in degrees
    Camera(float horizontalFOV, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

    Camera();


    void getV(Matrix4x4& result) const;

    void getP(Matrix4x4& result) const;

    Transform& getTransform();
    const Transform& getTransform() const;

};




#endif /* CAMERA_H */
