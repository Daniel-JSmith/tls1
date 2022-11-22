#define STB_IMAGE_IMPLEMENTATION
#include "PixelBuffer.h"

#include <stb_image.h>
#include <iostream>

#include "Color.h"

PixelBuffer::PixelBuffer(int width, int height) : width(width), height(height)
{
    pixelData.resize(width * height, 0);
    depth.resize(width * height, MAX_DEPTH);
}

PixelBuffer::PixelBuffer(const std::string& fileName)
{
    int channels = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData0 = stbi_load(fileName.c_str(), &width, &height, &channels, 4);
    uint32_t* imageData = reinterpret_cast<uint32_t*>(stbi_load(fileName.c_str(), &width, &height, &channels, 4));

    auto p0 = imageData[0];
    auto p1 = imageData[1];

    auto c0 = imageData0[0];
    auto c1 = imageData0[1];
    auto c2 = imageData0[2];
    auto c3 = imageData0[3];

    auto c4 = imageData0[4];
    auto c5 = imageData0[5];
    auto c6 = imageData0[6];
    auto c7 = imageData0[7];

    std::vector<unsigned char> pixelData0(imageData0, &imageData0[width * height * channels]);
    pixelData.insert(pixelData.end(), imageData, &imageData[width * height]);

    stbi_image_free(imageData);
}

int PixelBuffer::getWidth() const
{
    return width;
}

int PixelBuffer::getHeight() const
{
    return height;
}

inline int coordToIndex(int x, int y, int width)
{
    return y * width + x;
}

Vector4 PixelBuffer::getPixel(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return Vector4(0, 0, 0, 0);
    }

    return Vector4(Color::getVectorRepresentation(pixelData[coordToIndex(x, y, width)]));
}


void PixelBuffer::setPixel(int x, int y, const Vector4& newVector4)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        pixelData[coordToIndex(x, y, width)] = Color::getSerializedRepresentation(newVector4);
    }
}


void PixelBuffer::setPixelWithDepthTest(int x, int y, float z, const Vector4& newVector4)
{
    int pixelIndex = coordToIndex(x, y, width);
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return;
    }
    if (z < depth[pixelIndex])
    {
        pixelData[pixelIndex] = Color::getSerializedRepresentation(newVector4);
        depth[pixelIndex] = z;
    }
}

const std::vector<Color::SERIALIZED_REPRESENTATION>& PixelBuffer::getPixels() const
{
    return pixelData;
}

void PixelBuffer::clear(const Vector4& color)
{
    pixelData.assign(width * height, Color::getSerializedRepresentation(color));
    depth.assign(width * height, MAX_DEPTH);
}

void PixelBuffer::clear()
{
    clear(Vector4(0.0f, 0.5f, 0.0f, 1.0f));
}

