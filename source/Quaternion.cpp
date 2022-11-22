#include "Quaternion.h"

#include <math.h>

Quaternion::Quaternion(float s, float x, float y, float z) : s(s), x(x), y(y), z(z)
{
}

Quaternion::Quaternion() : s(1), x(0), y(0), z(0)
{
}

Quaternion::Quaternion(float radians, const Vector4& axis)
{
    s = cos(0.5f * radians);
    Vector4 vec = axis * (sin(0.5f * radians));
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

void Quaternion::getMatrix(Matrix4x4& result) const
{
    result.row0 = Vector4(1 - 2 * (y*y + z*z), 2 * (x*y - z*s), 2 * (x*z + y*s));
    result.row1 = Vector4(2 * (x*y + z*s), 1 - 2 * (x*x + z*z), 2 * (y*z - x*s));
    result.row2 = Vector4(2 * (x*z - y*s), 2 * (y*z + x*s), 1 - 2 * (x*x + y*y));
    result.row3 = Vector4(0, 0, 0, 1);
}

Quaternion Quaternion::getConjugate() const
{
    return Quaternion(s, -x, -y, -z);
}

Quaternion Quaternion::getInverse() const
{
    // assuming this is a unit Quaternion, its inverse is equal to its conjugate
    return getConjugate();
}

Quaternion Quaternion::operator*(const Quaternion& RHS) const
{
    Vector4 thisVec(x, y, z, 0);
    Vector4 RHSVec(RHS.x, RHS.y, RHS.z, 0);

    float resultScalar = s * RHS.s - thisVec.dot(RHSVec);
    Vector4 resultVec = RHSVec * s + thisVec * RHS.s + thisVec.cross(RHSVec);

    return Quaternion(resultScalar, resultVec.x, resultVec.y, resultVec.z);

}

Vector4 Quaternion::rotate(const Vector4& vec) const
{
    Quaternion v(0, vec.x, vec.y, vec.z);
    Quaternion result = (*this) * v * this->getConjugate(); 

    return Vector4(result.x, result.y, result.z, 0);
}
