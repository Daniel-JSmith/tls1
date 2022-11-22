#ifndef VERTEX_H
#define VERTEX_H

#include <tuple>
#include <vector>
#include <array>
#include "Vector4.h"
#include "Matrix4x4.h"

// TODO this should be extensible. Code using Vertex should take advantage of
// polymorphism, so if I want to return vertex attributes from a function, I
// need to decide on a method capable of returning a heterogeneous collection
// polymorphically. Maybe return a custom class containing attribute handles?
class Vertex
{
private:

public:

    static const int NUM_ATTRIBUTES = 4;

    Vector4 position;
    Vector4 normal;
    Vector4 uv;

    Vector4 eyePosition;

    using linearAttributesType = std::tuple<const decltype(position), const decltype(normal), const decltype(uv), const decltype(eyePosition)>;
    using perspectiveAttributesType = std::tuple<>;

    Vertex() = delete;
    Vertex(Vector4& position, Vector4& normal, Vector4& uv, Vector4& eyePosition);
    Vertex(const Vertex&) = default;
    Vertex(Vertex&&) = default;

    std::vector<Vector4> getAttributes() const;

    virtual linearAttributesType getLinearAttributes() const;
    virtual perspectiveAttributesType getPerspectiveAttributes() const;

    Vertex& operator=(const Vertex&) = default;
    Vertex& operator=(Vertex&&) = default;

    Vector4& operator[](int i);

    virtual ~Vertex() = default;
};

#endif /* VERTEX_H */
