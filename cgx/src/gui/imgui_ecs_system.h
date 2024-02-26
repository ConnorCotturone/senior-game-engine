// Copyright © 2024 Jacob Curlin

#include "../ecs/ecs_manager.h"
#include "../ecs/i_system.h"
#include "../ecs/ecs_types.h"

#ifndef IMGUIECSHANDLER_H
#define IMGUIECSHANDLER_H

namespace cgx::gui
{

    class ImguiECSSystem : public cgx::ecs::System
    {
    public:
        void Initialize(std::shared_ptr<cgx::ecs::ECSManager> ecs_manager);

        void DisplayEntityDropdown();
        void DisplayComponentEditors();

        void DisplayRenderComponentEditor(cgx::ecs::Entity entity);
        void DisplayTransformComponentEditor(cgx::ecs::Entity entity);
        void DisplayLightComponentEditor(cgx::ecs::Entity entity);

    private:
        std::shared_ptr<cgx::ecs::ECSManager> m_ecs_manager;        
        cgx::ecs::Entity m_current_entity;
    };

}

#endif // IMGUIECSHANDLER_H
