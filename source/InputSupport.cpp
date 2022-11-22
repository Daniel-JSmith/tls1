#include "InputSupport.h"

#include <iostream>

InputSupport::InputSupport()
{
    previousKeyState.assign(HIGHEST_KEYCODE, false);
    currentKeyState.assign(HIGHEST_KEYCODE, false);

    //SetCursorPos(screenCenter.x, screenCenter.y);

    //ShowCursor(false);
}

void InputSupport::registerKeyState(int keyCode, bool down)
{
   currentKeyState[keyCode] = down;
}

void InputSupport::update(GLFWwindow& windowHandle)
{
    // TODO it seems wasteful to copy the whole vector
    previousKeyState = currentKeyState;

    mouseMovedThisFrame = false;
}

void InputSupport::setMouseDelta(double x, double y)
{
    mouseXDelta = x;
    mouseYDelta = y;

    mouseMovedThisFrame = true;
}

void InputSupport::getMouseDelta(int& x, int& y) const
{
    if (mouseMovedThisFrame)
    {
        x = mouseXDelta;
        y = mouseYDelta;
    }
    else
    {
        x = y = 0;
    }
}

bool InputSupport::isDown(int keyCode) const
{
    // TODO consider how to handle an unsupported key code
    return currentKeyState[keyCode];
}

bool InputSupport::wasClicked(int keyCode) const
{
    bool result = !previousKeyState[keyCode] && currentKeyState[keyCode];
    return result;
}
