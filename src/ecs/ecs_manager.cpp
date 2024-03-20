// Copyright © 2024 Jacob Curlin

#include "ecs/ecs_manager.h"
#include <memory>

namespace cgx::ecs
{
    void ECSManager::Initialize()       
    {
        m_component_manager = std::make_unique<ComponentManager>();      
        m_entity_manager = std::make_unique<EntityManager>();
        m_event_manager = std::make_unique<EventManager>();
        m_system_manager = std::make_unique<SystemManager>();
    }

    Entity ECSManager::CreateEntity()
    {
        return m_entity_manager->CreateEntity();
    }

    void ECSManager::DestroyEntity(Entity entity)
    {
        m_entity_manager->DestroyEntity(entity);
        m_component_manager->EntityDestroyed(entity);
        m_system_manager->EntityDestroyed(entity);
    }

    std::vector<Entity> ECSManager::getActiveEntities() const
    {
        return m_entity_manager->GetActiveEntities();
    }

    Signature ECSManager::GetSignature(Entity entity) 
    {
        return m_entity_manager->GetSignature(entity);
    }

    void ECSManager::AddEventListener(EventId event_id, std::function<void(Event&)> const& listener)
    {
        m_event_manager->AddListener(event_id, listener);
    }

    void ECSManager::SendEvent(Event& event)
    {
        m_event_manager->SendEvent(event);
    }

    void ECSManager::SendEvent(EventId event_id)
    {
        m_event_manager->SendEvent(event_id);
    }
}