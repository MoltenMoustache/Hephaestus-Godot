#pragma once
#include "System.h"
#include "SharedComponents.h"
#include "World.h"
#include "godot_cpp/core/print_string.hpp"

namespace Test
{
    class TransformSystem : public System<WriteAccess<Test::Transform>, ReadAccess<Test::Velocity>>
    {
        public:
        void Tick(float deltaTime) override
        {
            for(auto [entity, transform, velocity] : GetWorld().GetView<Test::Transform, Test::Velocity>().each())
            {
                transform.x += velocity.x * deltaTime;
                transform.y += velocity.y * deltaTime;
                transform.z += velocity.z * deltaTime;
            }
        }
    };
}