// jacob curlin
// ECSManager.cpp
// 01/28/2024

#include "ECSManager.h"
#include <memory>

namespace ECS
{
    void ECSManager::Initialize()
    {
        m_componentManager = std::make_unique<ComponentManager>();
        m_entityManager = std::make_unique<EntityManager>();
        m_systemManager = std::make_unique<SystemManager>();
    }

    Entity ECSManager::CreateEntity()
    {
        return m_entityManager->CreateEntity();
    }

    void ECSManager::DestroyEntity(Entity entity)
    {
        m_entityManager->DestroyEntity(entity);
        m_componentManager->EntityDestroyed(entity);
        m_systemManager->EntityDestroyed(entity);
    }

    template<typename T>
    void ECSManager::RegisterComponent()
    {
        m_componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void ECSManager::AddComponent(Entity entity, T component)
    {
        m_componentManager->AddComponent<T>(entity, component);

        auto signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentType<T>(), true);
        m_entityManager->SetSignature(entity, signature);

        m_systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void ECSManager::RemoveComponent(Entity entity)
    {
        m_componentManager->RemoveComponent<T>(entity);

        auto signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentType<T>(), false);
        m_entityManager->SetSignature(entity, signature);

        m_systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& ECSManager::GetComponent(Entity entity)
    {
        return m_componentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType ECSManager::GetComponentType()
    {
        return m_componentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> ECSManager::RegisterSystem()
    {
        return m_systemManager->RegisterSystem<T>();
    }

    template<typename T>
    void ECSManager::SetSystemSignature(Signature signature)
    {
        m_systemManager->SetSignature<T>(signature);
    }





}