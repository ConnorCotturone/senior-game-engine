// Copyright © 2024 Jacob Curlin

#include "core/common.h"
#include "ecs/system_manager.h"

namespace cgx::ecs
{
    void SystemManager::EntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_systems)
        {
            auto const& system = pair.second;

            system->m_entities.erase(entity);
        }
    }

    void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        for (auto const& pair : m_systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& system_signature = m_signatures[type];

            if ((entitySignature & system_signature) == system_signature)
            {
                system->m_entities.insert(entity);
            }

            else
            {
                system->m_entities.erase(entity);   
            }
        }
    }
}