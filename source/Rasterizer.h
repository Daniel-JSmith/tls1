#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Vertex.h"
#include "ShaderSupport.h"
#include "PixelBuffer.h"

namespace Rasterizer
{

void draw(Vertex& vertex0,
          Vertex& vertex1,
          Vertex& vertex2,
          const Shader& shader,
          PixelBuffer& target);

}

#endif /* RASTERIZER_H */
