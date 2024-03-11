// Copyright © 2024 Jacob Curlin

// Implements a packed array structure for storage/management of a particular component type's data. 
// reference: https://austinmorlan.com/posts/entity_component_system/

#pragma once

#include "ecs/common.h"

namespace cgx::ecs
{
    class IComponentArray
    {

    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;

    }; // class IComponentArray

} // namespace cgx::ecs