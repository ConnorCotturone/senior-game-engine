// jacob curlin
// SystemManager.h
// 01/28/2023

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "ecs_types.h"
#include "i_system.h"
#include <memory>
#include <unordered_map>


namespace ECS
{

    class SystemManager
    {
    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem();

        template<typename T>
        void SetSignature(Signature signature);

        void EntityDestroyed(Entity entity);

        void EntitySignatureChanged(Entity entity, Signature entitySignature);

    private:
        std::unordered_map<const char*, Signature> m_signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
    };

}





#endif // SYSTEM_H

