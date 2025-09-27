#include "ECSRunner.h"
#include "GodotPhysicsHelpers.h"
#include "GodotRenderingHelpers.h"
#include "SystemManager.h"
#include "Alias.h"
#include "Systems/RenderingSystem.h"
#include "Systems/TransformSystem.h"
#include "Systems/CollisionDetectionSystem.h"
#include "Systems/CollisionTransformSystem.h"
#include "Systems/CollisionResolutionSystem.h"

#include "Systems/SharedComponents.h"
#include "godot_cpp/classes/environment.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/physics_server3d.hpp"
#include "godot_cpp/classes/rendering_server.hpp"
#include "godot_cpp/classes/world3d.hpp"
#include "godot_cpp/core/memory.hpp"
#include <memory>
#include <godot_cpp/classes/viewport.hpp>
#include "godot_cpp/classes/resource_loader.hpp"

using namespace godot;

bool isInitialized = false;
void ECSRunner::_process(double delta)
{
    if(!isInitialized)
    {  
        godot::Ref<World3D> world3d = get_viewport()->get_world_3d();
        Ref<Environment> env = memnew(Environment);
        env->set_background(Environment::BG_COLOR);
        env->set_bg_color(Color(1.0,0,0));
        world3d->set_environment(env);

        m_World = std::make_unique<ECS::World>();
        m_SystemManager = std::make_unique<ECS::SystemManager>(m_World.get());

        
        RID scenarioRID = get_viewport()->get_world_3d()->get_scenario();
        Test::Scenario& scenarioComp = m_World->AddComponent<Test::Scenario>(m_World->CreateEntity());
        scenarioComp.m_RID = scenarioRID;

        m_SystemManager->RegisterSystem<Test::RenderingSystem>();
        m_SystemManager->RegisterSystem<Test::TransformSystem>();
        m_SystemManager->RegisterSystem<Test::CollisionTransformSystem>();
        m_SystemManager->RegisterSystem<Test::CollisionDetectionSystem>();
        m_SystemManager->RegisterSystem<Test::CollisionResolutionSystem>();

        m_SystemManager->StartupSystems();

        ECS::EntityHandle entity = m_World->CreateEntity();
        m_World->AddComponent<Test::Mesh>(entity, GodotHelpers::Rendering::CreateMesh("res://Bomberman.obj", scenarioRID));
        m_World->AddComponent<Test::Transform>(entity);
        auto& velComp = m_World->AddComponent<Test::Velocity>(entity);
        velComp.z = -1.f;
        m_World->AddComponent<Test::CollisionShape>(entity, GodotHelpers::Physics::CreateCollisionShape());

        ECS::EntityHandle entity2 = m_World->CreateEntity();
        m_World->AddComponent<Test::Mesh>(entity2, GodotHelpers::Rendering::CreateMesh("res://Bomberman.obj", scenarioRID));
        auto& transformComp = m_World->AddComponent<Test::Transform>(entity2);
        transformComp.z = -10.f;
        m_World->AddComponent<Test::CollisionShape>(entity2, GodotHelpers::Physics::CreateCollisionShape());

        
        isInitialized = true;
    }

    if(m_SystemManager && m_World)
    {
        m_SystemManager->PreUpdateSystems(static_cast<float>(delta));
        m_SystemManager->UpdateSystems(static_cast<float>(delta));
        m_SystemManager->PostUpdateSystems(static_cast<float>(delta));
        m_World->Update(static_cast<float>(delta));
    }
}

void ECSRunner::_ready()
{
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://main.tscn");
    if (scene.is_valid()) {
        Node* root = scene->instantiate();
        add_child(root); // or get_tree()->get_root()->add_child(root);
        print_line("MainScene loaded and added to tree");
    } else {
        print_line("Failed to load MainScene.tscn");
    }
}
