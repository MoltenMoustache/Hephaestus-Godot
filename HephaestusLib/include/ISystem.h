#pragma once
#include <typeindex>
#include <vector>

namespace ECS
{
    class World;
}

using TypeIndices = std::vector<std::type_index>;

class ISystem
{
public:
    virtual ~ISystem() = default;

    virtual const TypeIndices& GetWriteAccess() const = 0;
    virtual const TypeIndices& GetReadAccess() const = 0;

    virtual void Startup() {}
    virtual void Shutdown() {}
    virtual void PreUpdate(float deltaTime = 0.0f) {}
    virtual void PostUpdate(float deltaTime = 0.0f) {}
    
    virtual void Tick(float deltaTime = 0.0f) {}
    
    virtual void AssignWorld(ECS::World* world) {}
};
