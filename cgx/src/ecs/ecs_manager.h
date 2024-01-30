// jacob curlin
// ECSManager.h
// 01/28/2024

#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include "entity_manager.h"
#include "system_manager.h"
#include "component_manager.h"

namespace ECS
{
    class ECSManager
    {
    public:
        void Initialize();

        Entity CreateEntity();

        void DestroyEntity(Entity entity);

        template<typename T>
        void RegisterComponent() 
        { 
            m_componentManager->RegisterComponent<T>(); 
        }

        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            m_componentManager->AddComponent<T>(entity, component);

            auto signature = m_entityManager->GetSignature(entity);
            signature.set(m_componentManager->GetComponentType<T>(), true);
            m_entityManager->SetSignature(entity, signature);

            m_systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {
            m_componentManager->RemoveComponent<T>(entity);

            auto signature = m_entityManager->GetSignature(entity);
            signature.set(m_componentManager->GetComponentType<T>(), false);
            m_entityManager->SetSignature(entity, signature);

            m_systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return m_componentManager->GetComponent<T>(entity);
        }


        template<typename T>
        ComponentType GetComponentType()
        {
            return m_componentManager->GetComponentType<T>();
        }

        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return m_systemManager->RegisterSystem<T>();
        }

        template<typename T>
        void SetSystemSignature(Signature signature)
        {
            m_systemManager->SetSignature<T>(signature);
        }

    private:
        std::unique_ptr<ComponentManager> m_componentManager;
        std::unique_ptr<EntityManager> m_entityManager;
        std::unique_ptr<SystemManager> m_systemManager;
    };
}



#endif // ECSMANAGER_H