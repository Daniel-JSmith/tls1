#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <vector>
#include <limits>
#include <string>

#include "Vector4.h"
#include "Color.h"

//const float MAX_DEPTH = -std::numeric_limits<float>::infinity();
const float MAX_DEPTH = 1.0f; 


// stores color and depth
// It would be better to allow user to specify attachments.
// Right now, PixelBuffer objects represent the frame buffer and textures,
// where the depth attachment is wasted
class PixelBuffer
{

private:

    std::vector<Color::SERIALIZED_REPRESENTATION> pixelData;

    std::vector<float> depth;

    // size of the buffer in pixels
    int width;
    int height;

public:

    PixelBuffer(int width, int height);

    // opens fileName and reads data into created PixelBuffer
    PixelBuffer(const std::string& fileName);

    // Returns width of buffer in pixels
    int getWidth() const;
    // Returns height of buffer in pixels
    int getHeight() const;

    Vector4 getPixel(int x, int y) const;

    // void setPixel(int index);
    // x,y pixels, from bottom left origin
    void setPixel(int x, int y, const Vector4& newColor);

    // only writes if z is less than current value in depth buffer
    // z is pixel z position in view space. Positive z is behind the camera.
    void setPixelWithDepthTest(int x, int y, float z, const Vector4& newColor);

    // return pixel data array
    const std::vector<Color::SERIALIZED_REPRESENTATION>& getPixels() const;

    // Sets every pixel to color
    void clear(const Vector4& color);

    void clear();

};


#endif /* PIXELBUFFER_H */

