// ComponentManager.cpp
// jacob curlin
// 01/26/2023

#include "ComponentManager.h"
#include "logging.h"

namespace ECS
{

    template<typename T>
    ComponentType ComponentManager::GetComponentType()
    {
        const char* typeName = typeid(T).name();

        PHX_ASSERT(m_componentTypes.find(typeName) != m_componentTypes.end(), "Component not registered before use.");

        return m_componentTypes[typeName];
    }

    template<typename T>
    void ComponentManager::AddComponent(Entity entity, T component)
    {
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void ComponentManager::RemoveComponent(Entity entity)
    {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T& ComponentManager::GetComponent(Entity entity)
    {
        return GetCommponentArray<T>()->GetData(entity);
    }

    void ComponentManager::EntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_componentArrays)
        {
            auto const& component = pair.second;

            component->EntityDestroyed(entity);
        }
    }

    template<typename T>
    std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
    {
        const char* typeName = typeid(T).name();

        PHX_ASSERT(m_componentTypes.find(typeName) != m_componentTypes.end(), "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
    }

}