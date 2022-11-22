#include "Transform.h"

Transform::Transform() : position(Vector4(0, 0, 0, 0)), scale(Vector4(1, 1, 1, 0))
{
}

Matrix4x4 Transform::getRotationMatrix() const
{
    Matrix4x4 result;
    rotation.getMatrix(result);

    return result;
}

Matrix4x4 Transform::getTranslationMatrix() const
{
    return Matrix4x4(Vector4(1, 0, 0, position.x),
                     Vector4(0, 1, 0, position.y),
                     Vector4(0, 0, 1, position.z),
                     Vector4(0, 0, 0, 1));
}

Matrix4x4 Transform::getScaleMatrix() const
{
    return Matrix4x4(Vector4(scale.x, 0, 0, 0),
                     Vector4(0, scale.y, 0, 0),
                     Vector4(0, 0, scale.z, 0),
                     Vector4(0, 0, 0, 1));
}

void Transform::getTRS(Matrix4x4& result) const
{
    result = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
}

void Transform::getInverseTR(Matrix4x4& result) const
{
    Matrix4x4 TInverse = Matrix4x4(Vector4(1, 0, 0, -position.x),
                                   Vector4(0, 1, 0, -position.y),
                                   Vector4(0, 0, 1, -position.z),
                                   Vector4(0, 0, 0, 1));

    Matrix4x4 RInverse;
    rotation.getConjugate().getMatrix(RInverse);

    result = RInverse * TInverse;
}

void Transform::offsetPosition(const Vector4& offset)
{
    position = position + offset;
}

void Transform::setPosition(const Vector4& position)
{
    this->position = position;
}

void Transform::setScale(const Vector4& scale)
{
    this->scale = scale;
}

void Transform::rotateWorld(const Quaternion& rotation)
{
    this->rotation = rotation * this->rotation;
}

void Transform::rotateSelf(const Quaternion& rotation)
{
    this->rotation = this->rotation * rotation;
}

void Transform::rotate(const Quaternion& rotation)
{
    rotateWorld(rotation);
}

