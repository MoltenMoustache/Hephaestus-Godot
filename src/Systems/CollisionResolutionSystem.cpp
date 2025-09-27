#include "CollisionResolutionSystem.h"
#include "SharedComponents.h"
#include "World.h"
#include "godot_cpp/core/print_string.hpp"

void Test::CollisionResolutionSystem::Tick(float deltaTime)
{
    for (auto [entity, hit] : GetWorld().GetView<Test::CollisionQueryResult>().each())
    {
        Test::Transform& transformComp = GetWorld().GetComponent<Test::Transform>(hit.m_SourceEntity);
        godot::Vector3 position = godot::Vector3(transformComp.x, transformComp.y, transformComp.z);
        position += hit.m_MinimumTranslationVector;

        transformComp.x = position.x;
        transformComp.y = position.y;
        transformComp.z = position.z;
    }
}