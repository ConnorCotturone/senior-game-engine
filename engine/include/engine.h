// jacob curlin
// engine.h
// 01/05/2023

#ifndef ENGINE_H
#define ENGINE_H


#include "../include/window.h"
#include "../include/input.h"
#include "../include/mesh.h"
#include "../include/model.h"
#include "../include/shader.h"
#include "../include/camera.h"
#include "../include/logging.h"
#include "../include/imgui_handler.h"
#include "../include/event_handler.h"

struct EngineSettings {
    int WindowWidth = 800;
    int WindowHeight = 600;
    // shader source / compile directory paths?
};

struct TimeData {
    double deltaTime;
    double lastTime;
};

struct MouseData {
    double xoffset;
    double yoffset;
};
    
class Engine
{
public:
    Engine();
    virtual ~Engine();

    void Run();

protected:
    virtual void Initialize();
    virtual void Update();
    virtual void Render();
    virtual void Shutdown();

protected:
    EngineSettings settings;
    TimeData m_timeData;

    Window* m_windowHandler;

    EventHandler* m_eventHandler;

    Input* m_inputHandler; 
    Camera* m_camera;
    Shader* m_lightShader;
    Shader* m_objShader;

    Model* m_subject;
    Model* m_lightSrc;

    ImguiHandler* m_imguiHandler;
    
    bool m_isRunning;
    bool m_imguiActive;
};

#endif // ENGINE_H