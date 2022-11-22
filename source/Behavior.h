#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Transform.h"
#include "InputSupport.h"

namespace Behavior
{

    void rotation(Transform& target, double secondsSinceLastCall, float rotateDegreesPerSecond, const Vector4& axis);

    void FPSCameraMovement(Transform& target, double secondsSinceLastCall, const InputSupport& inputSupport, float translateUnitsPerSecond, float rotateDegreesPerPixel);

}

#endif /* BEHAVIOR_H */
