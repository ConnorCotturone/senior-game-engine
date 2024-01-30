// component_manager.cpp
// jacob curlin
// 01/26/2023

#include "component_manager.h"
#include "../utility/logging.h"

namespace ECS
{
    void ComponentManager::EntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_componentArrays)
        {
            auto const& component = pair.second;

            component->EntityDestroyed(entity);
        }
    }

}