// Copyright © 2024 Jacob Curlin

#include "ecs/common.h"
#include "ecs/entity_registry.h"

namespace cgx::ecs
{

    EntityRegistry::EntityRegistry() : m_active_entity_count(0)  // initialize vector of s_max_entities   
    {
        for (Entity entity = 0; entity < s_max_entities; ++entity)
        {
            m_available_entities.push(entity);
        }
    }

    Entity EntityRegistry::CreateEntity()    // fetch first unused entity from entity vector
    {
        CGX_ASSERT(m_active_entity_count < s_max_entities, "Too many active entities."); 
        if (!(m_active_entity_count < s_max_entities)) { CGX_INFO("Active Entity Count : {}", m_active_entity_count); } 
        if (!(m_active_entity_count < s_max_entities)) { CGX_INFO("s_max_entities : {}", s_max_entities); }

        Entity id = m_available_entities.front();        // fetch 
        m_available_entities.pop();
        ++m_active_entity_count;

        return id;
    }

    void EntityRegistry::DestroyEntity(Entity entity)
    {
        CGX_ASSERT(entity < s_max_entities, "Entity out of range.");
        CGX_INFO("Destroying Entity {}", entity);

        m_signatures[entity].reset();   // reset entity's signature (bitset) 

        m_available_entities.push(entity);
        --m_active_entity_count;
    }

    void EntityRegistry::SetSignature(Entity entity, Signature signature)
    {
        CGX_ASSERT(entity < s_max_entities, "Entity out of range.");

        m_signatures[entity] = signature;
    }

    Signature EntityRegistry::GetSignature(Entity entity)
    {
        CGX_ASSERT(entity < s_max_entities, "Entity out of range.");

        return m_signatures[entity];
    }

    std::vector<Entity> EntityRegistry::GetActiveEntities() const
    {
        std::vector<Entity> active_entities;
        for (Entity entity = 0; entity < s_max_entities; ++entity)
        {
            if (m_signatures[entity].any())
            {
                active_entities.push_back(entity);
            }
        }
        return active_entities;
    }
}