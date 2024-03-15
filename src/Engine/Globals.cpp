#include "Engine/Globals.hpp"
#include "Engine/Other/Printer.hpp"

using namespace MyEngine;

std::unordered_map<unsigned, Entities::Entity> Globals::entityMap;
std::vector<Textures::ModelTexture> Globals::textureList;
std::vector<Models::TexturedModel> Globals::modelList;
// std::vector<Entities::Light> Globals::lightList;
std::vector<Water::WaterTile> Globals::waterTileList;

std::vector<Components::PlayerComponent> Globals::playerComponentList;
std::vector<Components::AABBComponent> Globals::aabbComponentList;
std::vector<Components::OBBComponent> Globals::obbComponentList;
std::vector<Components::RigidBodyComponent> Globals::rigidBodyComponentList;
std::vector<Components::RayComponent> Globals::rayComponentList;
std::vector<Components::CameraComponent> Globals::cameraComponentList;
std::vector<Components::LightComponent> Globals::lightComponentList;

const Entities::Entity* Globals::editorSelectedEntity = nullptr;

bool Globals::editorShowAddMenu = false;
bool Globals::editorShowInspectorMenu = false;

Entities::Entity* Globals::GetEntity(unsigned id)
{
    if (entityMap.find(id) != entityMap.end())
    {
        return &entityMap.at(id);
    }

    Printer::PrintError(Printer::ECS, "Entity [%d] couldn't be found in the entity map.", id);
    return nullptr;
}

Components::PlayerComponent* Globals::GetPlayerComponent(unsigned id)
{
    if (playerComponentList.empty())
    {
        Printer::PrintError(Printer::ECS, "Tried to fetch PlayerComp (%d), but the comp. list is empty!", id);
        return nullptr;
    }

    if (id > playerComponentList.size())
    {
        Printer::PrintError(Printer::ECS, "Tried to fetch PlayerComp (%d), but the id is out of bounds!", id);
        return nullptr;
    }

    return &playerComponentList.at(id);
}

Components::AABBComponent* Globals::GetAABBComponent(unsigned id);
Components::OBBComponent* Globals::GetOBBComponent(unsigned id);
Components::RigidBodyComponent* Globals::GetRigidBodyComponent(unsigned id);
Components::RayComponent* Globals::GetRayComponent(unsigned id);
