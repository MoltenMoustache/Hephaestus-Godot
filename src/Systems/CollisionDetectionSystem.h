#include "ComponentTypes.h"
#include "SharedComponents.h"
#include "System.h"
#include "godot_cpp/variant/rid.hpp"
#include <optional>

namespace Test
{
    class CollisionDetectionSystem : public System<WriteAccess<Test::CollisionSpaceSingleton>, ReadAccess<Test::Transform, Test::CollisionShape>>
    {
    public:
        virtual void Startup() override;
        virtual void Tick(float deltaTime) override;
    };
}