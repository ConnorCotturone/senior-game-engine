// jacob curlin
// engine.h
// 01/05/2023

#ifndef ENGINE_H
#define ENGINE_H

#include "../include/resources_paths.h"

#include "window.h"
#include "input_handler.h"
#include "imgui_handler.h"
#include "../components/transform.h"
#include "../ecs/ecs_manager.h"
#include "../event/event_handler.h"
#include "../render/camera.h"
#include "../render/mesh.h"
#include "../render/model.h"
#include "../render/shader.h"
#include "../utility/logging.h"

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

    ECS::ECSManager* m_ecsHandler;
    EventHandler* m_eventHandler;

    InputHandler* m_inputHandler; 
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