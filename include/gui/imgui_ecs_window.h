// Copyright © 2024 Jacob Curlin

#pragma once

#include "gui/imgui_window.h"
#include "ecs/ecs_manager.h"
#include "ecs/i_system.h"
#include "ecs/ecs_types.h"
#include "render/resource_manager.h"

namespace cgx::gui
{
    class ImGuiECSWindow : public cgx::ecs::System, public ImGuiWindow
    {
    public:
        ImGuiECSWindow(
            std::shared_ptr<cgx::ecs::ECSManager> ecs_manager,
            std::shared_ptr<cgx::render::ResourceManager> resource_manager);
            
        void Render() override;

        void RenderActiveEntitiesSection();

        void DisplayRenderComponentEditor(cgx::ecs::Entity entity);
        void DisplayTransformComponentEditor(cgx::ecs::Entity entity);
        void DisplayLightComponentEditor(cgx::ecs::Entity entity);

    private:
        std::shared_ptr<cgx::ecs::ECSManager>               m_ecs_manager;        
        std::shared_ptr<cgx::render::ResourceManager>     m_resource_manager;
        cgx::ecs::Entity                                    m_current_entity;
    };
}

