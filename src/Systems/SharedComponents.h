#pragma once
#include "Alias.h"
#include "ComponentTypes.h"
#include "godot_cpp/classes/input_event.hpp"
#include "godot_cpp/variant/rid.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include <cstdint>
#include <optional>

namespace Test
{
    // SINGLETON?
    struct Input : public Component
    {
        godot::InputEvent* m_Event = nullptr;
    };

    struct Transform : public Component
    {
        float x,y,z = 0.f;
    };

    struct Velocity : public Component
    {
        float x,y,z = 0.f;
    };

    // SINGLETON
    struct Scenario : public Component
    {
        std::optional<godot::RID> m_RID;
    };
     // SINGLETON
    struct CollisionSpaceSingleton : public Component
    {
        std::optional<godot::RID> m_SpaceRID;
    };

    struct CollisionQueryResult : public OneFrameComponent
    {
        ECS::EntityHandle m_SourceEntity;

        godot::Vector3 m_MinimumTranslationVector = godot::Vector3();
        godot::Vector3 m_Normal = godot::Vector3();
        float m_PenetrationDepth = 0.0f;
    };

    struct CollisionQueryRequest : public OneFrameComponent
    {
        
    };

    struct CollisionShape : public Component
    {
        std::optional<godot::RID> m_ShapeRID;
        std::optional<godot::RID> m_BodyRID;
    };
}