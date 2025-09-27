#pragma once
#include <entt.h>
#include "ComponentTypes.h"

namespace ECS
{
    using EntityHandle = entt::entity;
    using Registry = entt::registry;
}

template<typename... TComponents>
using RegistryQuery = entt::view<entt::get_t<TComponents...>>;

template<typename... TComponents>
using WorldView = entt::view<entt::get_t<TComponents...>>;