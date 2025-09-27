#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <memory>

#include "SystemManager.h"
#include "World.h"
#include "godot_cpp/classes/input_event.hpp"

class ECSRunner : public godot::Node {
    GDCLASS(ECSRunner, godot::Node)

    public:
    static void _bind_methods() {}
    ECSRunner() {}
    ~ECSRunner() {}

    void _process(double delta) override;
    void _ready() override;
    void _input(const godot::Ref<godot::InputEvent>& event) override;

    private:
    std::unique_ptr<ECS::World> m_World;
    std::unique_ptr<ECS::SystemManager> m_SystemManager;
};