// Copyright © 2024 Jacob Curlin

#include "core/common.h"
#include "ecs/entity_manager.h"

namespace cgx::ecs
{

    EntityManager::EntityManager() : m_active_entity_count(0)  // initialize vector of MAX_ENTITIES   
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            m_available_entities.push_back(entity);
        }
    }

    Entity EntityManager::CreateEntity()    // fetch first unused entity from entity vector
    {
        CGX_ASSERT(m_active_entity_count < MAX_ENTITIES, "Too many active entities."); 
        if (!(m_active_entity_count < MAX_ENTITIES)) { CGX_INFO("Active Entity Count : {}", m_active_entity_count); } 
        if (!(m_active_entity_count < MAX_ENTITIES)) { CGX_INFO("MAX_ENTITIES : {}", MAX_ENTITIES); }

        Entity id = m_available_entities.front();        // fetch 
        m_available_entities.pop_front();
        ++m_active_entity_count;

        return id;
    }

    void EntityManager::DestroyEntity(Entity entity)
    {
        CGX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");
        CGX_INFO("Destroying Entity {}", entity);

        m_signatures[entity].reset();   // reset entity's signature (bitset) 

        m_available_entities.push_front(entity);
        --m_active_entity_count;
    }

    void EntityManager::SetSignature(Entity entity, Signature signature)
    {
        CGX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");

        m_signatures[entity] = signature;
    }

    Signature EntityManager::GetSignature(Entity entity)
    {
        CGX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");

        return m_signatures[entity];
    }

    std::vector<Entity> EntityManager::GetActiveEntities() const
    {
        std::vector<Entity> active_entities;
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            if (m_signatures[entity].any())
            {
                active_entities.push_back(entity);
            }
        }
        return active_entities;
    }
}