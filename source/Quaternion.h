#ifndef QUATERNION_H
#define QUATERNION_H

#include "Matrix4x4.h"

// unit
class Quaternion
{

private:
    float s, x, y, z;

    Quaternion(float s, float x, float y, float z);

public:

    // creates identity quaternion
    Quaternion();

    // represents rotation of radians about axis
    Quaternion(float radians, const Vector4& axis);

    void getMatrix(Matrix4x4& result) const;

    // returns conjugate of this Quaternion
    Quaternion getConjugate() const;

    Quaternion getInverse() const;

    Quaternion operator*(const Quaternion& RHS) const;

    // returns vec rotated by this Quaternion
    Vector4 rotate(const Vector4& vec) const;
};
#endif /* QUATERNION_H */
