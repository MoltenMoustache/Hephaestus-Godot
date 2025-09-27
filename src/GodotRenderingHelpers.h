#pragma once
#include "godot_cpp/classes/rendering_server.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "Systems/RenderingSystem.h"

using namespace godot;
namespace GodotHelpers
{
    namespace Rendering
    {
        static Test::Mesh CreateMesh(const char* objPath, godot::RID scenario)
        {
            RenderingServer* server = RenderingServer::get_singleton();

            godot::RID instance = server->instance_create();   
            server->instance_set_scenario(instance, scenario);
            if(!instance.is_valid())
                godot::print_line("RenderingSystem: Instance failed to create");
            else
                godot::print_line("RenderingSystem: Instance created successfully");
            

            Ref<Resource> meshResource = godot::ResourceLoader::get_singleton()->load(objPath);
            if(!meshResource.is_valid())
                godot::print_line("RenderingSystem: Resource failed to load");
            else
                godot::print_line("RenderingSystem: Resource loaded successfully");

            server->instance_set_base(instance, meshResource->get_rid());

            Test::Mesh result;
            result.m_MeshRID = meshResource->get_rid();
            result.m_Instance = instance;
            return result;
        }
    }
}