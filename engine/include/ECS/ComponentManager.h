// jacob curlin
// ComponentManager.h
// 01/26/2023

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <unordered_map>
#include "Entity.h"
#include "Component.h"
#include "IComponentArray.h"

namespace ECS
{
    class ComponentManager
    {
    public:

        template<typename T>
        void RegisterComponent();

        template<typename T>
        ComponentType GetComponentType();

        template<typename T>
        void AddComponent(Entity entity, T component);

        template<typename T>
        void RemoveComponent(Entity entity);

        template<typename T>
        T& GetComponent(Entity entity);

        void EntityDestroyed(Entity entity);

    public:
        std::unordered_map<const char*, ComponentType> m_componentTypes{};
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays{};
        ComponentType m_nextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray();

    };


}


#endif // COMPONENTMANGER_H