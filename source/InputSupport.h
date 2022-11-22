#ifndef INPUTSUPPORT_H
#define INPUTSUPPORT_H

#include <vector>

#include <GLFW/glfw3.h>

// Container for keyboard and mouse state.
class InputSupport
{

private:

    static const int HIGHEST_KEYCODE = GLFW_KEY_LAST;
    
    // true represents down; false represents up
    std::vector<bool> previousKeyState;
    std::vector<bool> currentKeyState;

    int mouseXDelta, mouseYDelta;
    bool mouseMovedThisFrame;


public:

    enum KEYCODES
    {
        LEFT = GLFW_KEY_LEFT,
        DOWN = GLFW_KEY_DOWN,
        RIGHT = GLFW_KEY_RIGHT,
        UP = GLFW_KEY_UP
    };

    InputSupport();

    void update(GLFWwindow& windowHandle);

    void registerKeyState(int keyCode, bool down);

    // if pressed
    bool isDown(int keyCode) const;
    // if user started pressing this frame
    bool wasClicked(int keyCode) const;

    // pixel difference where down is negative y
    void setMouseDelta(double x, double y);
    void getMouseDelta(int& x, int& y) const;

};

#endif /* INPUTSUPPORT_H */
