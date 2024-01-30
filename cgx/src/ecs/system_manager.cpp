// jacob curlin
// SystemManager.cpp
// 01/28/2024

#include "system_manager.h"
#include "../utility/logging.h"

namespace ECS
{
    template<typename T>
    std::shared_ptr<T> SystemManager::RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        PHX_ASSERT(m_systems.find(typeName) == m_systems.end(), "Registering system more than once.");

        auto system = std::make_shared<T>();
        m_systems.insert({typeName, system});
        return system;
    }

    template<typename T>
    void SystemManager::SetSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        PHX_ASSERT(m_systems.find(typeName) != m_systems.end(), "System used before being registered.")

        m_signatures.insert({typeName, signature});
    }

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
            auto const& systemSignature = m_signatures[type];

            if ((entitySignature & systemSignature) == systemSignature)
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