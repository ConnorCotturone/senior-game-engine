// jacob curlin
// IComponentArray.h
// 01/28/2023

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "Entity.h"
#include "EntityManager.h"

namespace ECS
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        void InsertData(Entity entity, T component);
        void RemoveData(Entity entity);
        T& GetData(Entity entity);
        void EntityDestroyed(Entity entity) override;

    private:
        std::array<T, MAX_ENTITIES> m_componentArray;

        std::unordered_map<Entity, size_t> m_entityToIndexMap;
        std::unordered_map<size_t, Entity> m_indexToEntityMap;

        size_t m_size;

    };
}



#endif // COMPONENTARRAY_H