#ifndef RENDERING_H
#define RENDERING_H

#include <chrono>
#include "Drawable.h"
#include "Camera.h"
#include "ShaderSupport.h"
#include "PixelBuffer.h"

namespace Rendering
{

    const int RENDER_RESOLUTION_X = 300;
    const int RENDER_RESOLUTION_Y = 300;

    const int PRESENT_RESOLUTION_X = 1000;
    const int PRESENT_RESOLUTION_Y = 1000;

    const std::chrono::duration<float, std::milli> MIN_FRAME_TIME(16.66f);

    void draw(const Drawable& drawable, const Camera& camera, const Shader& shader, PixelBuffer& target);

}

#endif /* RENDERING_H */
