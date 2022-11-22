#ifndef SCENE_H
#define SCENE_H

#include <chrono>

#include "PixelBuffer.h"
#include "InputSupport.h"

class Scene
{

private:


protected:

typedef std::chrono::duration<float, std::ratio<1,1>> durationInSeconds;

public:

    virtual void update(durationInSeconds secondsSinceLastUpdate, const InputSupport& inputSupport) = 0;

    virtual void draw(PixelBuffer& renderTarget) const = 0;

};


#endif /* SCENE_H */

