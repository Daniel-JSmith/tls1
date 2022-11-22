#include "SampleScene.h"


#include <iostream>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Drawable.h"
#include "Camera.h"
#include "Vertex.h"
#include "LambertShader.h"
#include "PhongShader.h"
#include "CookTorranceShader.h"
#include "Rendering.h"
#include "CoordinateSystems.h"
#include "Behavior.h"


SampleScene::SampleScene() : drawable("Assets/monkle2.obj"),
                             lightPos(-2, 0, 5, 1),
                             albedo("Assets/fb-diff.png"),
                             roughness("Assets/fb-rough.png"),
                             ao("Assets/fb-ao.png"),
                             normalMap("Assets/fb-norm.png")
{
    camera.getTransform().offsetPosition(Vector4(0, 0, 2.5, 0));
}

void SampleScene::update(durationInSeconds secondsSinceLastUpdate, const InputSupport& inputSupport)
{
    //Behavior::rotation(drawable.getTransform(), secondsSinceLastUpdate.count(), 40, CoordinateSystems::UP);
    Behavior::FPSCameraMovement(camera.getTransform(), secondsSinceLastUpdate.count(), inputSupport, 2, 1);
}

void SampleScene::draw(PixelBuffer& renderTarget) const
{
    auto lightPosition = CoordinateSystems::worldToViewSpace(lightPos, camera);
    //auto lightPosition = lightPos;

    LambertShader lambert(lightPosition, albedo);
    PhongShader phong(lightPosition);
    CookTorranceShader cookTorrance(lightPosition, albedo, roughness, ao, normalMap);

    Rendering::draw(drawable, camera, phong, renderTarget);
}

