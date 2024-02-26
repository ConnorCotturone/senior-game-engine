// jacob curlin
// engine.h
// 01/05/2023

#ifndef ENGINE_H
#define ENGINE_H

#include "../include/resources_paths.h"

#include "window.h"
#include "input_handler.h"
#include "../ecs/ecs_manager.h"
#include "../event/event_handler.h"
#include "../gui/imgui_manager.h"
#include "../gui/imgui_ecs_system.h"
#include "../render/camera.h"
#include "../render/mesh.h"
#include "../render/model.h"
#include "../render/shader.h"
#include "../render/resource_manager.h"
#include "../utility/logging.h"

#include "../components/transform_component.h"
#include "../components/render_component.h"
#include "../components/light_component.h"

#include <filesystem>

struct EngineSettings {
    int window_width = 800;
    int window_height = 600;
    std::filesystem::path shader_dir = SHADER_DIRECTORY;
    std::filesystem::path asset_dir = DATA_DIRECTORY;
};

struct TimeData {
    double delta_time;
    double last_time;
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
    TimeData m_time_data;

    std::unique_ptr<cgx::graphics::ResourceManager> m_resource_manager;
    std::shared_ptr<cgx::ecs::ECSManager>           m_ecs_handler;
    std::unique_ptr<Window>                         m_window_handler;
    std::unique_ptr<cgx::event::EventHandler>       m_event_handler;
    std::unique_ptr<InputHandler>                   m_input_handler;
    std::unique_ptr<cgx::gui::ImguiManager>         m_imgui_manager;
    std::shared_ptr<cgx::gui::ImguiECSSystem>       m_imgui_ecs_system;
    std::unique_ptr<cgx::graphics::Camera>          m_camera;
   
    std::vector<cgx::ecs::Entity> m_entities;

    bool m_is_running;
    bool m_imgui_active;
};

#endif // ENGINE_H