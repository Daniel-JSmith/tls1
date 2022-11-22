#ifndef SAMPLESCENE_H
#define SAMPLESCENE_H

#include "Scene.h"

#include "Camera.h"
#include "Drawable.h"


// In this iteration of the engine, a Scene is responsible for storing and
// transforming trianges. A scene has a DrawController that expects triangles
// in screen space
class SampleScene : public Scene
{

private:

    Camera camera;
    Drawable drawable;
    Vector4 lightPos;
    PixelBuffer albedo;
    PixelBuffer roughness;
    PixelBuffer ao;
    PixelBuffer normalMap;

public:

    SampleScene();

    void update(durationInSeconds secondsSinceLastUpdate, const InputSupport& inputSupport) override;

    void draw(PixelBuffer& renderTarget) const override;

};



#endif /* SAMPLESCENE_H */
