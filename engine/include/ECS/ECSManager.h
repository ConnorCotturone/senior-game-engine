// jacob curlin
// ECSManager.h
// 01/28/2024

#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include "EntityManager.h"
#include "SystemManager.h"
#include "ComponentManager.h"

namespace ECS
{
    class ECSManager
    {
    public:
        void Initialize();

        Entity CreateEntity();

        void DestroyEntity(Entity entity);

        template<typename T>
        void RegisterComponent();

        template<typename T>
        void AddComponent(Entity entity, T component);

        template<typename T>
        void RemoveComponent(Entity entity);

        template<typename T>
        T& GetComponent(Entity entity);

        template<typename T>
        ComponentType GetComponentType();

        template<typename T>
        std::shared_ptr<T> RegisterSystem();

        template<typename T>
        void SetSystemSignature(Signature signature);

    private:
        std::unique_ptr<ComponentManager> m_componentManager;
        std::unique_ptr<EntityManager> m_entityManager;
        std::unique_ptr<SystemManager> m_systemManager;
    };









}



#endif // ECSMANAGER_H