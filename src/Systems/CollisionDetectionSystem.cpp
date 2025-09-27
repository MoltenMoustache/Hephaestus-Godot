#include "CollisionDetectionSystem.h"
#include "Alias.h"
#include "GodotHelpers.h"
#include "SharedComponents.h"
#include "World.h"

#include "godot_cpp/classes/physics_direct_space_state3d.hpp"
#include "godot_cpp/classes/physics_server3d.hpp"
#include "godot_cpp/classes/physics_shape_query_parameters3d.hpp"
#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/rid.hpp"
#include "godot_cpp/variant/transform3d.hpp"

void Test::CollisionDetectionSystem::Startup()
{
    // Setup space
    godot::RID physicsSpace = godot::PhysicsServer3D::get_singleton()->space_create();
    auto spaceEntity = GetWorld().CreateEntity();
    auto& spaceComp = GetWorld().AddComponent<Test::CollisionSpaceSingleton>(spaceEntity);
    spaceComp.m_SpaceRID = physicsSpace;
}

void Test::CollisionDetectionSystem::Tick(float deltaTime)
{
    godot::PhysicsServer3D* singleton = godot::PhysicsServer3D::get_singleton();

    // Grab active physics space
    ECS::EntityHandle singletonEntity = GetWorld().GetView<Test::CollisionSpaceSingleton>().front();
    auto& singletonComp = GetWorld().GetComponent<Test::CollisionSpaceSingleton>(singletonEntity);

    godot::PhysicsDirectSpaceState3D* spaceState = singleton->space_get_direct_state(singletonComp.m_SpaceRID.value());

    for(auto [entity, transform, collisionShape, vel] : GetWorld().GetView<Test::Transform, Test::CollisionShape, Test::Velocity>().each())
    {
        godot::Ref<godot::PhysicsShapeQueryParameters3D> query = memnew(godot::PhysicsShapeQueryParameters3D);
        query->set_shape_rid(collisionShape.m_ShapeRID.value());
        query->set_transform(GodotHelpers::GetTransform3D(transform.x, transform.y, transform.z));
        query->set_margin(0.0f);
        query->set_collide_with_bodies(true);
        query->set_exclude(godot::Array::make(collisionShape.m_BodyRID.value()));

        godot::Array contacts = spaceState->collide_shape(query, 1);
        for(int i = 0; i < contacts.size(); i+=2)
        {
            godot::Vector3 sourceContact = contacts[i];
            godot::Vector3 hitContact = contacts[i+1];

            // Create hit result
            ECS::EntityHandle hitEntity = GetWorld().CreateEntity();
            Test::CollisionQueryResult& result = GetWorld().AddComponent<Test::CollisionQueryResult>(hitEntity);
            result.m_SourceEntity = entity;
            result.m_PenetrationDepth = (sourceContact - hitContact).length();
            result.m_Normal = (hitContact - sourceContact).normalized();
            result.m_MinimumTranslationVector = result.m_Normal * result.m_PenetrationDepth;
        }
    }
}