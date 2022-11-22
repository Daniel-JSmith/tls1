#ifndef MATRIX4X4_h
#define MATRIX4X4_h

#include "Vector4.h"

class Matrix4x4
{

private:


public:

    Vector4 row0, row1, row2, row3;

    Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3);
    // identity
    Matrix4x4();

    const Vector4& getRow0() const;
    const Vector4& getRow1() const;
    const Vector4& getRow2() const;
    const Vector4& getRow3() const;
    Vector4 getCol0() const;
    Vector4 getCol1() const;
    Vector4 getCol2() const;
    Vector4 getCol3() const;

    // invert the elements of the main diagonal. I added this function to
    // easily invert scaling matrices, as inverting the main diagonal of a
    // scaling matrix is equivalent to inversion
    void invertMainDiagonal();

    // transpose this matrix
    void transpose();

    // mat vec multiplication
    Vector4 operator*(const Vector4& RHS) const;

    // mat mat multiplication
    Matrix4x4 operator*(const Matrix4x4& RHS) const;

    Vector4& operator[](int index);

};

#endif /* MATRIX4X4_H */
