// Copyright © 2024 Jacob Curlin

#include "ecs/component_registry.h"

namespace cgx::ecs
{
    void ComponentRegistry::EntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_component_arrays)
        {
            auto const& component = pair.second;

            component->EntityDestroyed(entity);
        }
    }

}