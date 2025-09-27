#pragma once
#include <tuple>

#include "ISystem.h"

namespace ECS
{
    class World;
}

template <typename... TComp>
using WriteAccess = std::tuple<TComp...>;
    
template <typename... TComp>
using ReadAccess = std::tuple<TComp...>;

template<typename Write, typename Read>
class System : public ISystem
{
public:
    virtual ~System() = default;
    const TypeIndices& GetWriteAccess() const override { return m_WriteAccess; }
    const TypeIndices& GetReadAccess() const override { return m_ReadAccess; }
    
    void AssignWorld(ECS::World* world) override
    {
        m_World = world;
    }
    
private:
    template<typename Tuple>
    static TypeIndices MakeTypeVector()
    {
        TypeIndices types{};
        std::apply([&](auto... tuple)
        {
            (types.emplace_back(typeid(std::decay_t<decltype(tuple)>())), ...);
        }, Tuple{});

        return types;
    }

    inline static TypeIndices m_WriteAccess = MakeTypeVector<Write>();
    inline static TypeIndices m_ReadAccess = MakeTypeVector<Read>();

protected:
    ECS::World* m_World = nullptr;
    ECS::World& GetWorld() const
    { 
        return *m_World;
    }
};
