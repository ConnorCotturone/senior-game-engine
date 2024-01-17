// jacob curlin
// imguiwindow.h
// 01/17/2023

#include <GLFW/glfw3.h>

class ImguiWindow
{

public:
    ImguiWindow() {}
    ~ImguiWindow() {}

    void Initialize(GLFWwindow* window);
    void Shutdown();

    void StartFrame();
    void EndFrame();

private:



};