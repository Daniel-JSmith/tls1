#ifndef COORDINATESYSTEMS_H
#define COORDINATESYSTEMS_H

#include "Vector4.h"
#include "Matrix4x4.h"
#include "Camera.h"

// Contains some functions for moving between coordinate systems. There's
// currently no way to easily make changes like flipping the sign of an axis. I
// would like to be able to make changes like that e.g. for compatibility with
// Vulkan, D3d or whatever, but it's not supported (yet?).
//
// The definition of coordinate systems aren't perfectly encapsulated. Some
// other code makes the projection matrix, for instance, but really there
// should be little other dependent code
// 
// NDC is -1 <= x <= -1
//        -1 <= y <= -1
//         0 <= z <=  1
// screen is 0 <= x <= 1
//           0 <= y <= 1
//           0 <= z <= 1
namespace CoordinateSystems
{

    const Vector4 RIGHT(1, 0, 0, 0);
    const Vector4 FORWARD(0, 0, -1, 0);
    const Vector4 UP(0, 1, 0, 0);

    bool withinClipVolume(const Vector4& clip);
    // perspective division
    Vector4 clipToNDC(const Vector4& clip);
    Vector4 NDCToScreen(const Vector4& NDC);
    Vector4 screenToDevice(const Vector4& screen, int deviceWidth, int deviceHeight);

    Matrix4x4 getProjectionMatrix(float halfHorizontalFOV, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

    Vector4 worldToViewSpace(const Vector4& vec, const Camera& view);
}


#endif /* COORDINATESYSTEMS_H */
