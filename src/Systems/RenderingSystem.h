#pragma once
#include "System.h"
#include "ComponentTypes.h"
#include "SharedComponents.h"
#include "World.h"
#include "godot_cpp/classes/mesh.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/variant/basis.hpp"
#include "godot_cpp/variant/rid.hpp"
#include <optional>
namespace Test
{
    struct Mesh : public Component
    {
        std::optional<godot::RID> m_MeshRID;
        std::optional<godot::RID> m_Instance;
    };

    class RenderingSystem : public System<WriteAccess<Test::Mesh>, ReadAccess<Test::Mesh, Test::Transform>>
    {
    public:
        virtual void Tick(float deltaTime) override;
    };
}