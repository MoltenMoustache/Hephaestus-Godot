#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <memory>

#include "SystemManager.h"
#include "World.h"

class ECSRunner : public godot::Node {
    GDCLASS(ECSRunner, godot::Node)

    public:
    static void _bind_methods() {}
    ECSRunner() {}
    ~ECSRunner() {}

    void _process(double delta) override;
    void _ready() override;

    private:
    std::unique_ptr<ECS::World> m_World;
    std::unique_ptr<ECS::SystemManager> m_SystemManager;
};