#include "Color.h"

#include <algorithm>
#include <limits>
#include <type_traits>

const uint32_t Color::R_MASK = 0x000000FF;
const uint32_t Color::G_MASK = 0x0000FF00;
const uint32_t Color::B_MASK = 0x00FF0000;
const uint32_t Color::A_MASK = 0xFF000000;

// convert [0, 1] float to [0, 255] int
inline uint8_t toInt(float input)
{
    return static_cast<uint8_t>(input * std::numeric_limits<uint8_t>::max());
}

template <typename T>
T clampChannel(T&& value)
{
    using valueType = typename std::remove_reference<decltype(value)>::type;
    value = std::max(value, static_cast<valueType>(0));
    value = std::min(value, static_cast<valueType>(std::numeric_limits<uint8_t>::max()));
    return value;
}

float getChannelData(uint32_t data, uint32_t mask)
{
    return (data & mask) / static_cast<float>(mask);
}

Vector4 clampColor(const Vector4& color)
{
    auto result = color;
    result.x = std::min(1.0f, color.x);
    result.y = std::min(1.0f, color.y);
    result.z = std::min(1.0f, color.z);
    result.w = std::min(1.0f, color.w);
    result.x = std::max(0.0f, result.x);
    result.y = std::max(0.0f, result.y);
    result.z = std::max(0.0f, result.z);
    result.w = std::max(0.0f, result.w);
    return result;
}

Vector4 Color::getVectorRepresentation(uint32_t data)
{
    return Vector4(getChannelData(data, R_MASK),
                   getChannelData(data, G_MASK),
                   getChannelData(data, B_MASK),
                   getChannelData(data, A_MASK));
}

Color::SERIALIZED_REPRESENTATION Color::getSerializedRepresentation(const Vector4& vec)
{
    auto clampedVec = clampColor(vec);
    uint32_t result = toInt(clampedVec.w);
    result <<= 8;
    result |= toInt(clampedVec.z);
    result <<= 8;
    result |= toInt(clampedVec.y);
    result <<= 8;
    result |= toInt(clampedVec.x);

    return result;
}

