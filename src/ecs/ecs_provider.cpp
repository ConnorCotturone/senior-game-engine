// Copyright © 2024 Jacob Curlin

#include "ecs/ecs_provider.h"

namespace cgx::ecs
{
    ECSProvider::ECSProvider(cgx::core::Time& time)
        : UpdateTimeBase(time)
        , m_component_registry(std::make_unique<ComponentRegistry>())
        , m_entity_registry(std::make_unique<EntityRegistry>())
        , m_system_registry(std::make_unique<SystemRegistry>())
        , m_event_handler(std::make_unique<event::EventHandler>())
    {}
    
    ECSProvider::~ECSProvider() {}

    Entity ECSProvider::CreateEntity()
    {
        return m_entity_registry->CreateEntity();
    }

    void ECSProvider::DestroyEntity(Entity entity)
    {
        m_entity_registry->DestroyEntity(entity);
        m_component_registry->EntityDestroyed(entity);
        m_system_registry->EntityDestroyed(entity);
    }

    std::vector<Entity> ECSProvider::getActiveEntities() const
    {
        return m_entity_registry->GetActiveEntities();
    }

    Signature ECSProvider::GetSignature(Entity entity) 
    {
        return m_entity_registry->GetSignature(entity);
    }

    void ECSProvider::UnsubscribeEvent(event::IEventDelegate* event_delegate)
    {
        m_event_handler->RemoveEventCallback(event_delegate);
    }

} // namespace cgx::ecs