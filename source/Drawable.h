#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Model.h"
#include "Transform.h"

class Drawable
{

private:

    Model model;
    Transform transform;

public:
    
    Drawable(const std::string& modelFilename);

    const Model& getModel() const;

    Transform& getTransform();
    const Transform& getTransform() const;

};

#endif /* DRAWABLE_H */
