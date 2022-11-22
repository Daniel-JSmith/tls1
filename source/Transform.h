#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector4.h"
#include "Quaternion.h"

class Transform
{

private:


public:

    Vector4 position;
    Vector4 scale;
    Quaternion rotation;
    
    Transform();

    Matrix4x4 getRotationMatrix() const;
    Matrix4x4 getTranslationMatrix() const;
    Matrix4x4 getScaleMatrix() const;

    void getTRS(Matrix4x4& result) const;
    void getInverseTR(Matrix4x4& result) const;

    void offsetPosition(const Vector4& offset);
    void setPosition(const Vector4& position);
    void setScale(const Vector4& scale);

    void rotateWorld(const Quaternion& rotation);
    void rotateSelf(const Quaternion& rotation);
    // rotate this Transform
    void rotate(const Quaternion& rotation);
};

#endif /* TRANSFORM_H */
