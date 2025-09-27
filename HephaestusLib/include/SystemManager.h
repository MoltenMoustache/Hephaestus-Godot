#pragma once

#include <memory>
#include <vector>

#include "ISystem.h"

namespace ECS
{
    class World;
    template <typename TSys>
    concept IsSystem = std::derived_from<TSys, ISystem>;
    
    class SystemManager
    {
    public:
        SystemManager() = default;
        ~SystemManager() = default;
        SystemManager(const SystemManager&) = delete;
        SystemManager(SystemManager&&) = delete;
        SystemManager& operator=(const SystemManager&) = delete;
        SystemManager& operator=(SystemManager&&) = delete;

        SystemManager(ECS::World* world) : m_World(world) {}
        
        template <IsSystem TSystem>
        ISystem& RegisterSystem()
        {
            // HasAccess(TSystem::WriteAccess);
            auto& newSystem = m_Systems.emplace_back(std::make_unique<TSystem>());
            if (m_World)
            {
                newSystem->AssignWorld(m_World);
            }
            SortSystems();
            
            return *newSystem.get();
        }

        void StartupSystems();
        
        void PreUpdateSystems(float deltaTime);
        void UpdateSystems(float deltaTime);
        void PostUpdateSystems(float deltaTime);
        
        void ShutdownSystems();

    private:
        // When registering a system, ensure it is ordered correctly based on Write/Read access
        bool SortSystems();

    private:
        std::vector<std::unique_ptr<ISystem>> m_Systems;
        ECS::World* m_World = nullptr;
    };
}
