// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/system.h"
#include "ecs/ecs_manager.h"

namespace cgx::core
{
    class PhysicsSystem : public cgx::ecs::System
    {
    public:
        void Initialize(std::shared_ptr<cgx::ecs::ECSManager> ecs_manager);

        void Update(float dt);

    private:
        std::shared_ptr<cgx::ecs::ECSManager> m_ecs_manager;
    }; // class PhysicsSystem

} // namespace cgx::core