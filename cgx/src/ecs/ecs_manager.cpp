// jacob curlin
// ecs_manager.cpp
// 01/28/2024

#include "ecs_manager.h"
#include <memory>

namespace cgx::ecs
{
    void ECSManager::Initialize()       
    {
        m_componentManager = std::make_unique<ComponentManager>();      
        m_entityManager = std::make_unique<EntityManager>();
        m_systemManager = std::make_unique<SystemManager>();
    }

    Entity ECSManager::CreateEntity()
    {
        return m_entityManager->CreateEntity();
    }

    void ECSManager::DestroyEntity(Entity entity)
    {
        m_entityManager->DestroyEntity(entity);
        m_componentManager->EntityDestroyed(entity);
        m_systemManager->EntityDestroyed(entity);
    }
}