// jacob curlin
// engine.h
// 01/05/2023

#ifndef ENGINE_H
#define ENGINE_H

#include "../include/resources_paths.h"

#include "window.h"
#include "input_handler.h"
#include "imgui_handler.h"
#include "../ecs/ecs_manager.h"
#include "../event/event_handler.h"
#include "../render/camera.h"
#include "../render/mesh.h"
#include "../render/model.h"
#include "../render/shader.h"
#include "../render/resource_manager.h"
#include "../utility/logging.h"

#include "../components/transform_component.h"
#include "../components/render_component.h"

#include <filesystem>

struct EngineSettings {
    int WindowWidth = 800;
    int WindowHeight = 600;
    std::filesystem::path shader_dir = SHADER_DIRECTORY;
    std::filesystem::path asset_dir = DATA_DIRECTORY;
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
    EngineSettings m_settings;
    TimeData m_timeData;

    Window* m_windowHandler;

    InputHandler* m_inputHandler; 
    ImguiHandler* m_imguiHandler;

    cgx::ecs::ECSManager* m_ecsHandler;
    cgx::event::EventHandler* m_eventHandler;
    cgx::graphics::Camera* m_camera;
    
    std::vector<cgx::ecs::Entity> m_entities;

    cgx::graphics::ResourceManager* m_resource_manager;

    bool m_isRunning;
    bool m_imguiActive;
};

#endif // ENGINE_H