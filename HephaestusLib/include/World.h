#pragma once
#include <cassert>

#include "Alias.h"
#include "ComponentTypes.h"
#include "entt.h"

namespace ECS
{
    class World
    {
    public:        
        void Update(float deltaTime)
        {
            ClearOneFrameRegistry();
        }

        ECS::EntityHandle CreateEntity()
        {
            ECS::EntityHandle entity = m_PrimaryRegistry.create();
            ECS::EntityHandle oneFrameEntity = m_OneFrameRegistry.create(entity);

            assert(entity == oneFrameEntity);
            return entity;
        }

        template <TStandardComp TComp, typename... Args>
        TComp& AddComponent(const ECS::EntityHandle& entity, Args&&... args)
        {
            return m_PrimaryRegistry.emplace<TComp>(entity, std::forward<Args>(args)...);
        }

        template <TOneFrameComp TComp, typename... Args>
        TComp& AddComponent(const ECS::EntityHandle& entity, Args&&... args)
        {
            return m_OneFrameRegistry.emplace<TComp>(entity, std::forward<Args>(args)...);
        }

        template <TStandardComp TComp>
        void RemoveComponent(const ECS::EntityHandle& entity)
        {
            m_PrimaryRegistry.remove<TComp>(entity);
        }

        template <TOneFrameComp TComp>
        void RemoveComponent(const ECS::EntityHandle& entity)
        {
            m_OneFrameRegistry.remove<TComp>(entity);
        }
        
        template<typename... Cs>
        static constexpr bool AllStandard = (TStandardComp<Cs> && ...);

        template<typename... Cs>
        static constexpr bool AllOneFrame = (TOneFrameComp<Cs> && ...);

        template<typename... TComponents>
        Registry& GetOwningRegistry()
        {
            if constexpr (AllStandard<TComponents...>)
                return m_PrimaryRegistry;
            else
                return m_OneFrameRegistry;
        }

        template<typename TComponent>
        const Registry& GetOwningRegistry() const
        {
            if constexpr (TStandardComp<TComponent>)
                return m_PrimaryRegistry;
            else
                return m_OneFrameRegistry;
        }

        template<typename TComponent>
        TComponent& GetComponent(EntityHandle entity) {
            return GetOwningRegistry<TComponent>().template get<TComponent>(entity);
        }

        template<typename TComponent>
        const TComponent& GetComponent(EntityHandle entity) const {
            return GetOwningRegistry<TComponent>().template get<TComponent>(entity);
        }

        template<typename TComponent>
        bool HasComponent(EntityHandle entity) const {
            return GetOwningRegistry<TComponent>().template all_of<TComponent>(entity);
        }

        template<typename... TComponents>
        WorldView<TComponents...> GetView()
        {
            static_assert(AllStandard<TComponents...> || AllOneFrame<TComponents...>);
            
            if constexpr (AllStandard<TComponents...>)
                return m_PrimaryRegistry.view<TComponents...>();
            else
                return m_OneFrameRegistry.view<TComponents...>();
        }

    private:
        void ClearOneFrameRegistry()
        {
            for (auto [id, storage] : m_OneFrameRegistry.storage())
            {
                storage.clear();
            }
        }

    public:
        // TODO: Make a Registry interface
        // IRegistry contains the standard accessors of a regular entt::registry
        // Have a StandardRegistry and a SingletonRegistry
        // SingletonComponents don't map to entities, so we just need a map<typeid, TComponent> or a vector
        Registry m_PrimaryRegistry;
        Registry m_OneFrameRegistry;
    };
}
