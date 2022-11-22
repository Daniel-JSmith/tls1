#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

#include "Vector4.h"

class Color
{

private:

    static const uint32_t R_MASK, G_MASK, B_MASK, A_MASK;

public:

    Color() = delete;

    using SERIALIZED_REPRESENTATION = uint32_t;

    static Vector4 getVectorRepresentation(uint32_t data);
    static SERIALIZED_REPRESENTATION getSerializedRepresentation(const Vector4& vec);

};

#endif /* COLOR_H */
