#include "Matrix4x4.h"

#include <algorithm>


Matrix4x4::Matrix4x4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3) : row0(row0), row1(row1), row2(row2), row3(row3)
{

}

Matrix4x4::Matrix4x4() : Matrix4x4(Vector4(1, 0, 0, 0),
                                   Vector4(0, 1, 0, 0),
                                   Vector4(0, 0, 1, 0),
                                   Vector4(0, 0, 0, 1))
{
}

const Vector4& Matrix4x4::getRow0() const
{
    return row0;
}

const Vector4& Matrix4x4::getRow1() const
{
    return row1;
}

const Vector4& Matrix4x4::getRow2() const
{
    return row2;
}

const Vector4& Matrix4x4::getRow3() const
{
    return row3;
}

Vector4 Matrix4x4::getCol0() const
{
    return Vector4(row0.x, row1.x, row2.x, row3.x);
}

Vector4 Matrix4x4::getCol1() const
{
    return Vector4(row0.y, row1.y, row2.y, row3.y);
}

Vector4 Matrix4x4::getCol2() const
{
    return Vector4(row0.z, row1.z, row2.z, row3.z);
}

Vector4 Matrix4x4::getCol3() const
{
    return Vector4(row0.w, row1.w, row2.w, row3.w);
}

void Matrix4x4::invertMainDiagonal()
{

    for (int i = 0; i < 3; i++)
    {
        auto& element = operator[](i)[i];
        if (element != 0)
        {
            element = 1.0f / element;
        }
    }
}

void Matrix4x4::transpose()
{
    std::swap(row1.x, row0.y);

    std::swap(row2.x, row0.z);
    std::swap(row2.y, row1.z);

    std::swap(row3.x, row0.w);
    std::swap(row3.y, row1.w);
    std::swap(row3.z, row2.w);
}


Vector4 Matrix4x4::operator*(const Vector4& RHS) const
{
    return Vector4(
        row0.dot(RHS),
        row1.dot(RHS),
        row2.dot(RHS),
        row3.dot(RHS)
        );
}

Vector4 multiplyRow(const Vector4& row, const Matrix4x4& RHS)
{
    return Vector4(row.dot(RHS.row0.x, RHS.row1.x, RHS.row2.x, RHS.row3.x),
                   row.dot(RHS.row0.y, RHS.row1.y, RHS.row2.y, RHS.row3.y),
                   row.dot(RHS.row0.z, RHS.row1.z, RHS.row2.z, RHS.row3.z),
                   row.dot(RHS.row0.w, RHS.row1.w, RHS.row2.w, RHS.row3.w));
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& RHS) const
{
    return Matrix4x4(multiplyRow(row0, RHS),
                     multiplyRow(row1, RHS),
                     multiplyRow(row2, RHS),
                     multiplyRow(row3, RHS)
                    );
}

Vector4& Matrix4x4::operator[](int index)
{
    if (index == 0)
    {
        return row0;
    }
    else if (index == 1)
    {
        return row1;
    }
    else if (index == 2)
    {
        return row2;
    }
    // It would be better to check bounds
    else
    {
        return row3;
    }
}
