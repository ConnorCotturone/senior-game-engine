// jacob curlin
// imguiwindow.h
// 01/17/2023

#include <GLFW/glfw3.h>

class ImguiHandler
{

public:
    ImguiHandler() {}
    ~ImguiHandler() {}

    void Initialize(GLFWwindow* window);
    void Shutdown();

    void Render();

private:



};