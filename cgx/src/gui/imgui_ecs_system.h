// Copyright © 2024 Jacob Curlin

#ifndef IMGUIECSHANDLER_H
#define IMGUIECSHANDLER_H

#include "../components/transform_component.h"
#include "../components/render_component.h"
#include "../components/light_component.h"

#include "../ecs/ecs_manager.h"
#include "../ecs/i_system.h"
#include "../ecs/ecs_types.h"
#include "../render/resource_manager.h"

namespace cgx::gui
{

    class ImguiECSSystem : public cgx::ecs::System
    {
    public:
        void Initialize(
            std::shared_ptr<cgx::ecs::ECSManager> ecs_manager,
            std::shared_ptr<cgx::graphics::ResourceManager> resource_manager
        );

        void RenderECSMenu();

        void RenderActiveEntitiesSection();


        void DisplayRenderComponentEditor(cgx::ecs::Entity entity);
        void DisplayTransformComponentEditor(cgx::ecs::Entity entity);
        void DisplayLightComponentEditor(cgx::ecs::Entity entity);

    private:
        std::shared_ptr<cgx::ecs::ECSManager>               m_ecs_manager;        
        std::shared_ptr<cgx::graphics::ResourceManager>     m_resource_manager;
        cgx::ecs::Entity                                    m_current_entity;
    };

}

#endif // IMGUIECSHANDLER_H
