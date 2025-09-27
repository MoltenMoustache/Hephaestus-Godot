#pragma once
#include <type_traits>

struct Component
{
};

struct OneFrameComponent : Component
{
};
    
template <typename TComp>
concept TOneFrameComp = std::is_base_of<OneFrameComponent, TComp>::value;

// basically declared to avoid GetView<Component, OneFrameComponent> until support for that is added
template <typename TComp>
concept TStandardComp = !std::is_base_of<OneFrameComponent, TComp>::value;