#include "Behavior.h"
#include "CoordinateSystems.h"
#include <cmath>

void Behavior::rotation(Transform& target, double secondsSinceLastCall, float rotateDegreesPerSecond, const Vector4& axis)
{
    auto radPerSecond = rotateDegreesPerSecond * (M_PI / 180.0f);
    Quaternion rotation(radPerSecond * secondsSinceLastCall, axis);
    target.rotate(rotation);
}

void Behavior::FPSCameraMovement(Transform& target, double secondsSinceLastCall, const InputSupport& inputSupport, float translateUnitsPerSecond, float rotateDegreesPerPixel)
{
    auto LR = target.rotation.rotate(CoordinateSystems::RIGHT);
    auto FB = target.rotation.rotate(CoordinateSystems::FORWARD);

    if (inputSupport.isDown(InputSupport::KEYCODES::LEFT))
    {
        target.offsetPosition(LR * -translateUnitsPerSecond * secondsSinceLastCall);
    }
    if (inputSupport.isDown(InputSupport::KEYCODES::RIGHT))
    {
        target.offsetPosition(LR * translateUnitsPerSecond * secondsSinceLastCall);
    }
    if (inputSupport.isDown(InputSupport::KEYCODES::DOWN))
    {
        target.offsetPosition(FB * -translateUnitsPerSecond * secondsSinceLastCall);
    }
    if (inputSupport.isDown(InputSupport::KEYCODES::UP))
    {
        target.offsetPosition(FB * translateUnitsPerSecond * secondsSinceLastCall);
    }
    int mouseXDelta, mouseYDelta;
    inputSupport.getMouseDelta(mouseXDelta, mouseYDelta);
    Quaternion xRot(-rotateDegreesPerPixel * (M_PI / 180.0f) * mouseXDelta, Vector4(0, 1, 0, 0));
    Quaternion yRot(rotateDegreesPerPixel * (M_PI / 180.0f) * mouseYDelta, Vector4(1, 0, 0, 0));
    target.rotateSelf(yRot);
    target.rotateWorld(xRot);
}
