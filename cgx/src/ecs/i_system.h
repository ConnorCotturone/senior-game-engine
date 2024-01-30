// jacob curlin
// ISystem.h
// 01/28/2024

#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include "entity.h"

namespace ECS
{
    class System
    {
    public:
        std::set<Entity> m_entities;
    };
}

#endif // SYSTEM_H