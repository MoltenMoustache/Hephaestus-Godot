#pragma once
#include "GodotHelpers.h"
#include "System.h"
#include "SharedComponents.h"
#include "World.h"
#include "godot_cpp/classes/physics_server3d.hpp"

namespace Test
{
    class CollisionTransformSystem : public System<WriteAccess<Test::CollisionShape>, ReadAccess<Test::Transform>>
    {
        public:
        void Tick(float deltaTime) override
        {
            ECS::EntityHandle singletonEntity = GetWorld().GetView<Test::CollisionSpaceSingleton>().front();
            auto& singletonComp =GetWorld().GetComponent<Test::CollisionSpaceSingleton>(singletonEntity);

            for(auto [entity, transform, collisionShape] : GetWorld().GetView<Test::Transform, Test::CollisionShape>().each())
            {
                godot::PhysicsServer3D::get_singleton()->body_set_space(collisionShape.m_BodyRID.value(), singletonComp.m_SpaceRID.value());
                godot::PhysicsServer3D::get_singleton()->body_set_state(collisionShape.m_BodyRID.value(), godot::PhysicsServer3D::BODY_STATE_TRANSFORM, GodotHelpers::GetTransform3D(transform.x, transform.y, transform.z));
            }
        }
    };
}