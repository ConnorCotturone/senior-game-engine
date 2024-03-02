// Copyright © 2024 Jacob Curlin

#pragma once

#define GL_SILENCE_DEPRECATION

#include "core/common.h"
#include "core/window.h"
#include "core/input_handler.h"

#include "ecs/ecs_manager.h"
#include "ecs/components/transform_component.h"
#include "ecs/components/render_component.h"
#include "ecs/components/light_component.h"
#include "event/event_handler.h"

#include "gui/imgui_manager.h"
#include "gui/imgui_render_window.h"
#include "gui/imgui_ecs_window.h"

#include "render/camera.h"
#include "render/mesh.h"
#include "render/model.h"
#include "render/shader.h"
#include "render/resource_manager.h"
#include "render/framebuffer.h"

#include "utility/logging.h"
#include "utility/paths.h"      // cmake-configured shader/asset paths

#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

namespace cgx::core {

    struct EngineSettings {
        uint32_t window_width = 1920;
        uint32_t window_height = 1080;
        uint32_t render_width = 1280;
        uint32_t render_height = 720;

        std::filesystem::path shader_dir = SHADERS_DIRECTORY;
        std::filesystem::path asset_dir = ASSETS_DIRECTORY;
    };

    struct TimeData {
        double delta_time;
        double last_time;
    };

    class Engine {
    public:
        Engine();

        virtual ~Engine() = default;

        void Run();

    protected:
        virtual void Initialize();

        virtual void Update();

        virtual void Render();

        virtual void Shutdown();

    protected:
        EngineSettings m_settings;
        TimeData m_time_data;

        // unique
        std::unique_ptr<cgx::core::Window> m_window_handler;
        std::unique_ptr<cgx::event::EventHandler> m_event_handler;
        std::unique_ptr<InputHandler> m_input_handler;
        std::unique_ptr<cgx::render::Camera> m_camera;

        std::shared_ptr<cgx::render::Framebuffer> m_framebuffer;

        // shared
        std::shared_ptr<cgx::ecs::ECSManager> m_ecs_manager;
        std::shared_ptr<cgx::render::ResourceManager> m_resource_manager;

        std::unique_ptr<cgx::gui::ImGuiManager> m_imgui_manager;
        std::unique_ptr<cgx::gui::ImGuiRenderWindow> m_imgui_render_window;
        std::unique_ptr<cgx::gui::ImGuiECSWindow> m_imgui_ecs_window;

        bool m_is_running;
        bool m_imgui_active;
    };

}