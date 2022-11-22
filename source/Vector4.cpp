#include "Vector4.h"

#include <math.h>

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

Vector4::Vector4(float x, float y, float z) : x(x), y(y), z(z), w(0)
{
}

Vector4& Vector4::operator+=(const Vector4& RHS)
{
    x += RHS.x;
    y += RHS.y;
    z += RHS.z;
    w += RHS.w;

    return *this;
}

Vector4& Vector4::operator-=(const Vector4& RHS)
{
    return *this += -RHS;
}

Vector4 Vector4::operator+(const Vector4& RHS) const
{
    Vector4 result = *this;
    result += RHS;
    return result;
}

Vector4 Vector4::operator-(const Vector4& RHS) const
{
    auto result = *this;
    result -= RHS;
    return result;
}

Vector4& Vector4::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Vector4& Vector4::operator/=(float scalar)
{
    return *this *= (1 / scalar);
}

Vector4 Vector4::operator*(float scalar) const
{
    /*
   return Vector4(x * scalar,
                  y * scalar,
                  z * scalar,
                  w * scalar);
                  */
    Vector4 result = *this;
    result *= scalar;
    return result;
}

Vector4 Vector4::operator/(float scalar) const
{
    return *this * (1 / scalar);
}

Vector4 Vector4::operator-() const
{
    return Vector4(-x, -y, -z, -w);
}

bool Vector4::operator==(const Vector4& RHS) const
{
    return x == RHS.x
        && y == RHS.y
        && z == RHS.z
        && w == RHS.w;
}

float& Vector4::operator[](int index)
{
    // It would be nice to check bounds here
    if (index == 0)
    {
        return x;
    }
    else if (index == 1)
    {
        return y;
    }
    else if (index == 2)
    {
        return z;
    }
    else 
    {
        return w;
    }
}

float Vector4::dot(float x, float y, float z, float w) const
{
    float result = this->x * x;
    result += this->y * y;
    result += this->z * z;
    result += this->w * w;
    return result;
}

float Vector4::dot(const Vector4& RHS) const
{
    return this->dot(RHS.x, RHS.y, RHS.z, RHS.w);
}


Vector4 Vector4::cross(const Vector4& RHS) const
{
    Vector4 result(0, 0, 0, 0);
    result.x = this->y * RHS.z - this->z * RHS.y;
    result.y = this->z * RHS.x - this->x * RHS.z;
    result.z = this->x * RHS.y - this->y * RHS.x;
    return result;
}

float Vector4::magnitude() const
{
    return sqrt(x * x + y * y + z * z + y * y);
}

Vector4 Vector4::normalized() const
{
    return *this / this->magnitude();
}

Vector4 operator*(float scalar, const Vector4& RHS)
{
    return RHS * scalar;
}

