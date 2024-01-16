// jacob curlin
// input.h
// 01/05/2023

#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input {

public:
    Input(GLFWwindow* window);
    ~Input();

    bool isKeyPressed(int key) const;
    void getMouseOffset(double& xoffset, double& offset);

private:
    GLFWwindow* m_window;

    double mouseX;
    double mouseY;
    bool firstMouse;
};

#endif // INPUT_H