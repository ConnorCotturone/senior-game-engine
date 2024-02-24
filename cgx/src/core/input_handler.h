// jacob curlin
// input_handler.h
// 01/05/2023

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <GLFW/glfw3.h>

class InputHandler {

public:
    InputHandler(GLFWwindow* window);
    ~InputHandler();

    bool IsKeyPressed(int key) const;
    void getMouseOffset(double& xoffset, double& yoffset);
    void resetMouseOffset();

    bool ignoreNextMouseUpdate;

private:
    GLFWwindow* m_window;

    double m_mouseX;
    double m_mouseY;
    bool m_firstMouse;
};

#endif // INPUTHANDLER_H