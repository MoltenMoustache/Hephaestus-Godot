#pragma once
#include "Systems/SharedComponents.h"
#include "godot_cpp/classes/physics_server3d.hpp"

namespace GodotHelpers
{
    namespace Physics
    {
        static Test::CollisionShape CreateCollisionShape()
        {
            godot::PhysicsServer3D* physics = godot::PhysicsServer3D::get_singleton();
            
            Test::CollisionShape result;            
            result.m_ShapeRID = physics->box_shape_create();

            godot::Vector3 extents(1.f,1.f,1.f);
            physics->shape_set_data(result.m_ShapeRID.value(), extents);

            result.m_BodyRID = physics->body_create();
            physics->body_add_shape(result.m_BodyRID.value(),result.m_ShapeRID.value());

            return result;
        }
    }
}