#ifndef GLOBALS_H
#define GLOBALS_H

#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/ECS/Components/OBBComponent.hpp"
#include "Engine/ECS/Components/PlayerComponent.hpp"
#include "Engine/ECS/Components/AABBComponent.hpp"
#include "Engine/ECS/Components/RayComponent.hpp"
#include "Engine/ECS/Components/RigidBodyComponent.hpp"
#include "Engine/ECS/Components/RayComponent.hpp"
#include "Engine/ECS/Components/CameraComponent.hpp"
#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/ECS/Entities/Light.hpp"
#include "Engine/Shaders/Water/WaterTile.hpp"
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace MyEngine {
    namespace Globals {
        extern std::unordered_map<unsigned, Entities::Entity> entityMap;
        extern std::vector<Components::PlayerComponent> playerComponentList; // TODO: reeval. if it should be a list
        extern std::vector<Components::AABBComponent> aabbComponentList;
        extern std::vector<Components::OBBComponent> obbComponentList;
        extern std::vector<Components::RigidBodyComponent> rigidBodyComponentList;
        extern std::vector<Components::RayComponent> rayComponentList;
        extern std::vector<Components::CameraComponent> cameraComponentList;
        extern std::vector<Components::LightComponent> lightComponentList;

        // TODO: add search by name functions for these
        extern std::vector<Textures::ModelTexture> textureList;
        extern std::vector<Models::TexturedModel> modelList;

        // extern std::vector<Entities::Light> lightList;
        extern std::vector<Water::WaterTile> waterTileList;

        extern const Entities::Entity* editorSelectedEntity;

        extern bool editorShowAddMenu;
        extern bool editorShowInspectorMenu;

        Entities::Entity* GetEntity(unsigned id);
        Components::PlayerComponent* GetPlayerComponent(unsigned id);
        Components::AABBComponent* GetAABBComponent(unsigned id);
        Components::OBBComponent* GetOBBComponent(unsigned id);
        Components::RigidBodyComponent* GetRigidBodyComponent(unsigned id);
        Components::RayComponent* GetRayComponent(unsigned id);
    }
}

#endif
