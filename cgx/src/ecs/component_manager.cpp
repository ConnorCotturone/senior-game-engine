// Copyright © 2024 Jacob Curlin

#include "component_manager.h"
#include "../utility/logging.h"

namespace cgx::ecs
{
    void ComponentManager::EntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_component_arrays)
        {
            auto const& component = pair.second;

            component->EntityDestroyed(entity);
        }
    }

}