// Copyright © 2024 Jacob Curlin

#include "core/physics_system.h"
#include "ecs/components/transform_component.h"
#include "ecs/components/rigid_body.h"

namespace cgx::core
{
    void PhysicsSystem::Initialize(std::shared_ptr<cgx::ecs::ECSManager> ecs_manager)
    {
        m_ecs_manager = ecs_manager;
    }

    void PhysicsSystem::Update(float dt)
    {
        for (auto const& entity : m_entities)
        {
            auto& rigid_body = m_ecs_manager->GetComponent<RigidBody>(entity);
            auto& transform = m_ecs_manager->GetComponent<TransformComponent>(entity);

            transform.position += rigid_body.velocity * dt;
            rigid_body.velocity += rigid_body.acceleration * dt;
        }
    }
}