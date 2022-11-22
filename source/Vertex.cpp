#include "Vertex.h"

Vertex::Vertex(Vector4& position, Vector4& normal, Vector4& uv, Vector4& eyePosition) : position(position), normal(normal), uv(uv), eyePosition(eyePosition)
{

}

Vertex::linearAttributesType Vertex::getLinearAttributes() const
{
    return linearAttributesType(position, normal, uv, eyePosition);
}

Vertex::perspectiveAttributesType Vertex::getPerspectiveAttributes() const
{
    return std::make_tuple();
}

std::vector<Vector4> Vertex::getAttributes() const
{
    return {position, normal, uv, eyePosition};
}

Vector4& Vertex::operator[](int i)
{
    if (i == 0)
    {
        return position;
    }
    else if (i == 1)
    {
        return normal;
    }
    else if (i == 2)
    {
        return uv;
    }
    else
    {
        return eyePosition;
    }
}
