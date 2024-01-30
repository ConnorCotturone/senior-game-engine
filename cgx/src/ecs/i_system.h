// jacob curlin
// ISystem.h
// 01/28/2024

#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "ecs_types.h"
#include <set>

namespace ECS
{
    class System
    {
    public:
        std::set<Entity> m_entities;
    };
}

#endif // ISYSTEM_H