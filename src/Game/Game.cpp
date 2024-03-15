#include "Game/Game.hpp"
#include "Engine/ECS/ComponentManagement.hpp"
#include <cstddef>

void Game::Start() {
    DemoLvl_InitVars();
    DemoLvl_StartingState();

    engine.Run();
}

void Game::DemoLvl_InitVars() {
    // TEXTURES
    Textures::ModelTexture bushTexture(Rendering::Loader::LoadTexture("bush2.png"), 1, 0, true, true);

    // MODELS
    Models::TexturedModel sceneModel(Rendering::OBJLoader::LoadOBJModel("scene.obj"), Globals::textureList[0]);
    Models::TexturedModel bushModel(Rendering::OBJLoader::LoadOBJModel("bush.obj"), Globals::textureList[3]);
    Models::TexturedModel charModel(Rendering::OBJLoader::LoadOBJModel("char.obj"), Globals::textureList[0]);

    // ENTITIES
    unsigned tmpID;
    Entities::CreateEntity("scene", Globals::modelList[1], glm::vec3(0, -3, 0));

    tmpID = Entities::CreateEntity("bush", Globals::modelList[2], glm::vec3(0, 0, -10));
    Components::CreateComponent(Components::OBB, tmpID);
    Components::CreateComponent(Components::RIGID_BODY, tmpID, .1);

    tmpID = Entities::CreateEntity("bush2", Globals::modelList[2], glm::vec3(20, 0, -10));
    Components::CreateComponent(Components::OBB, tmpID);
    Components::CreateComponent(Components::RIGID_BODY, tmpID, .1);

    tmpID = Entities::CreateEntity("player", Globals::modelList[3], glm::vec3(0,5,-20));
    Components::CreateComponent(Components::PLAYER_COMPONENT, tmpID); // TODO: check if duplicate
    Components::CreateComponent(Components::OBB, tmpID);

    tmpID = Entities::CreateEntity("cube", Globals::modelList[0], glm::vec3(0, 3, 0));
    Components::CreateComponent(Components::OBB, tmpID);
    Components::CreateComponent(Components::RIGID_BODY, tmpID, .1);

    // LIGHTS
    // TODO add static lights (only load when something changes)
    tmpID = Entities::CreateEntity("sun", Globals::modelList[0], glm::vec3(20, 100, 0));
    Components::CreateComponent(Components::LIGHT, tmpID);

    // Globals::lightList.push_back(Entities::Light(glm::vec3(20, 100, 0), glm::vec3(1, 1, 1)));
    // Globals::lightList.push_back(Entities::Light(glm::vec3(0, 2, -10), glm::vec3(0, 10, 0), glm::vec3(10, 0.1, 0.02)));
    // Globals::lightList.push_back(Entities::Light(glm::vec3(0, 2, 50), glm::vec3(1, 0.5, 0), glm::vec3(1, 0.01, 0.002)));

    // WATER
    Globals::waterTileList.push_back(Water::WaterTile(0, -10, -10));
}

void Game::DemoLvl_StartingState() {
    // Globals::rigidBodyComponentList.at(1).SetVelocity(glm::vec3(-1, 0, 0), 0.3);
    Globals::rigidBodyComponentList.at(1).SetAcceleration(glm::vec3(-1, 0, 0), 0.05);
    // Globals::rigidBodyComponentList.at(1).Rotate(glm::vec3(0, 1, 0), 1);
    // Globals::rigidBodyComponentList.at(0).Rotate(glm::vec3(0, 1, 0), 0.5);
    // Globals::rigidBodyComponentList.at(2).Rotate(glm::vec3(0, 1, 0), 0.5);
}
