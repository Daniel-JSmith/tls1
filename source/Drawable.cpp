#include "Drawable.h"

Drawable::Drawable(const std::string& modelFilename) : model(modelFilename)
{
}

const Model& Drawable::getModel() const 
{
    return model;
}

Transform& Drawable::getTransform()
{
    return const_cast<Transform&>(static_cast<const Drawable&>(*this).getTransform());
}

const Transform& Drawable::getTransform() const
{
    return transform;
}
