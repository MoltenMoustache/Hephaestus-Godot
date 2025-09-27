#pragma once
#include "godot_cpp/variant/transform3d.hpp"

namespace GodotHelpers
{
    
    static godot::Transform3D GetTransform3D(float x, float y, float z)
    {
        godot::Vector3 position = godot::Vector3(x, y, z);

        godot::Basis rotation_basis = godot::Basis();
        rotation_basis = rotation_basis.scaled(godot::Vector3(1.f, 1.f, 1.f));

        return godot::Transform3D(rotation_basis, position);
    }
}