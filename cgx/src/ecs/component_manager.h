// jacob curlin
// component_manager.h
// 01/26/2023

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ecs_types.h"
#include "component_array.h"
#include "../utility/logging.h"

#include <memory>
#include <unordered_map>

namespace cgx::ecs
{
    class ComponentManager
    {
    public:

        template<typename T>
        void RegisterComponent()
        {
            const char* typeName = typeid(T).name();

            CGX_ASSERT(m_componentTypes.find(typeName) == m_componentTypes.end(), "Registering component type more than once.");

            m_componentTypes.insert({typeName, m_nextComponentType});
            m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

            ++m_nextComponentType;
        }

        template<typename T>
        ComponentType GetComponentType()
        {
            const char* typeName = typeid(T).name();

            CGX_ASSERT(m_componentTypes.find(typeName) != m_componentTypes.end(), "Component not registered before use.");

            return m_componentTypes[typeName];
        }

        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            GetComponentArray<T>()->InsertData(entity, component);
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return GetComponentArray<T>()->GetData(entity);
        }

        void EntityDestroyed(Entity entity);

    public:
        std::unordered_map<const char*, ComponentType> m_componentTypes{};
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays{};
        ComponentType m_nextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray()
        {
            const char* typeName = typeid(T).name();

            CGX_ASSERT(m_componentTypes.find(typeName) != m_componentTypes.end(), "Component not registered before use.");

            return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
        }

    };

}


#endif // COMPONENTMANAGER_H