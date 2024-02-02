// jacob curlin
// event_handler.h
// 01/25/2023


#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <GLFW/glfw3.h>
#include <functional>
#include <vector>

namespace cgx::event
{
    class EventHandler {
    public:

        using KeyCallback = std::function<void(int, int, int, int)>;

        using MouseCallback = std::function<void(double, double)>;

        EventHandler(GLFWwindow* window);

        void RegisterKeyCallback(const KeyCallback& callback);

        void RegisterMouseCallback(const MouseCallback& callback);

        void Update();

    private:
        GLFWwindow* m_window;
        static std::vector<KeyCallback> m_keyCallbacks;
        static std::vector<MouseCallback> m_mouseCallbacks;

        static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void GLFWMouseCallback(GLFWwindow* window, double xpos, double ypos);
    };

}

#endif // EVENTHANDLER_H