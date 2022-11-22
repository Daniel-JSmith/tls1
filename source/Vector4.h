#ifndef VECTOR4_H
#define VECTOR4_H

class Vector4
{
private:


public:

    // vector components are so primitive that they should be public. I believe
    // PBRT made the same decision
    float x,y,z,w;

    Vector4(float x, float y, float z, float w);
    Vector4(float x, float y, float z);
    Vector4(const Vector4&) = default;
    Vector4(Vector4&&) = default;

    Vector4& operator=(const Vector4&) = default;
    Vector4& operator=(Vector4&&) = default;

    Vector4& operator+=(const Vector4& RHS);
    Vector4& operator-=(const Vector4& RHS);

    Vector4 operator+(const Vector4& RHS) const;
    Vector4 operator-(const Vector4& RHS) const;

    Vector4& operator *=(float scalar);
    Vector4& operator /=(float scalar);

    // scalar multiplication
    Vector4 operator*(float scalar) const;
    Vector4 operator/(float scalar) const;

    Vector4 operator-() const;

    bool operator==(const Vector4& RHS) const;

    float& operator[](int index);

    //float getX() const;
    //float getY() const;
    //float getZ() const;
    //float getW() const;
    //void setX(float value);
    //void setY(float value);
    //void setZ(float value);
    //void setW(float value);
    
    float dot(const Vector4& RHS) const;
    float dot(float x, float y, float z, float w) const;
    Vector4 cross(const Vector4& RHS) const;

    float magnitude() const;
    Vector4 normalized() const;

    ~Vector4() = default;
};

Vector4 operator*(float scalar, const Vector4& RHS);

#endif /* VECTOR4_H */
