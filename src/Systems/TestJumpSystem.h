#pragma once
#include "System.h"
#include "SharedComponents.h"
#include "World.h"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/core/print_string.hpp"

namespace Test
{
    class TestJumpSystem : public System<WriteAccess<Test::Velocity>, ReadAccess<Test::Input>>
    {
        public:
        void Tick(float deltaTime) override
        {
            for(auto [entity, velocity] : GetWorld().GetView<Test::Velocity>().each())
            {
                ECS::EntityHandle singletonEntity = m_World->GetView<Test::Input>().front();
                Test::Input& input = m_World->GetComponent<Test::Input>(singletonEntity);

                bool isPressed = godot::Input::get_singleton()->is_action_pressed("jump");
                if(isPressed)
                    velocity.y = 1.f;
                else 
                    velocity.y = 0.f;
            }
        }
    };
}