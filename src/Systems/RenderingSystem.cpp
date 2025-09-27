#pragma once
#include "RenderingSystem.h"

#include "World.h"
#include "GodotHelpers.h"
#include "godot_cpp/classes/rendering_server.hpp"
#include "godot_cpp/variant/transform3d.hpp"
#include "godot_cpp/variant/rid.hpp"
#include "godot_cpp/variant/vector3.hpp"

void Test::RenderingSystem::Tick(float deltaTime)
{
    auto rs = godot::RenderingServer::get_singleton();

    for(auto [entity, meshComp, transformComp] : GetWorld().GetView<Test::Mesh, Test::Transform>().each())
    {
        if(meshComp.m_Instance.has_value())
        {
            rs->instance_set_transform(meshComp.m_Instance.value(), GodotHelpers::GetTransform3D(transformComp.x, transformComp.y, transformComp.z));
        }
        //else if (scenarioRID.is_valid())
        //{
            //godot::print_line("RenderingSystem: Scenario RID: ", scenarioRID);
            //godot::RID instance = rs->instance_create();            
            //rs->instance_set_scenario(instance, scenarioRID);
            //
            //if(!instance.is_valid())
            //    godot::print_line("RenderingSystem: Instance failed to create");
            //else
            //    godot::print_line("RenderingSystem: Instance created successfully");
            //
            //auto meshResource = godot::ResourceLoader::get_singleton()->load("res://Bomberman.obj");
            //if(!meshResource.is_valid())
            //    godot::print_line("RenderingSystem: Resource failed to load");
            //else
            //    godot::print_line("RenderingSystem: Resource loaded successfully");
            //godot::Ref<godot::Mesh> meshCast = godot::Object::cast_to<godot::Mesh>(meshResource.ptr());
            //if(!meshCast.is_valid())
            //{
            //    godot::print_line("RenderingSystem: Resource correctly loaded, but is not a mesh.");
            //}
            //else
            //{
            //    godot::print_line("RenderingSystem: Mesh correctly loaded.");
            //}
            //
            //godot::Transform3D meshTransform = GodotHelpers::GetTransform3D(transformComp.x, transformComp.y, transformComp.z);
            //rs->instance_set_transform(meshComp.meshInstance.value(), meshTransform);
        //}
    }
}