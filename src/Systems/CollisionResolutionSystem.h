#include "SharedComponents.h"
#include "System.h"

namespace Test
{
    class CollisionResolutionSystem : public System<WriteAccess<>, ReadAccess<Test::CollisionQueryResult>>
    {
    public:
        virtual void Tick(float deltaTime) override;
    };
}