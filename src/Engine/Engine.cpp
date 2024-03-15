#include "Engine/Engine.hpp"
#include "Engine/Globals.hpp"
#include "imgui/imgui.h"

using namespace MyEngine;

char name[20] = "";
char texturePath[30] = "";
char modelPath[30] = "";


Engine::Engine() :
    m_camera(),
    m_mouseRay(Other::MouseRay(m_camera, Rendering::MasterRenderer::GetProjectionMatrix()))
{
    Rendering::DisplayManager::Create();
    InputEngine::Input::Init();
    UI_Init();
    LoadDefaults();
    Utilities::SaveSystem();
}

void Engine::Run() {
    Rendering::MasterRenderer renderer; // TODO turn into static

    Water::WaterFrameBuffer waterFBOs;
    Water::WaterShader waterShader;
    Water::WaterRenderer waterRenderer(waterShader, Rendering::MasterRenderer::GetProjectionMatrix(), waterFBOs);

    SetMemberVars();

    while (!Rendering::DisplayManager::ShouldClose()) {
        UI_CreateFrames();
        GameSystemsUpdate();
        UI_Update();

        WaterRenderPasses(renderer, m_camera, waterFBOs, Globals::waterTileList);
        renderer.RenderScene(Globals::lightComponentList, m_camera, glm::vec4(0, -1, 0, 15));
        waterRenderer.Render(Globals::waterTileList, m_camera, Globals::lightComponentList[0]);

        MainLoopEnd();
    }

    CleanUp(waterFBOs, renderer);
}

void Engine::LoadDefaults() {
    Textures::ModelTexture blankTexture(Rendering::Loader::LoadTexture("blank.png"), 1, 0, false, false);
    Textures::ModelTexture colliderTexture01(Rendering::Loader::LoadTexture("collider01.png"), 1, 0, true, true);
    Textures::ModelTexture colliderTexture02(Rendering::Loader::LoadTexture("collider02.png"), 1, 0, true, true);

    Models::TexturedModel cubeModel(Rendering::OBJLoader::LoadOBJModel("cube.obj"), Globals::textureList[0]);
}

// ECS, physics etc. updates
void Engine::GameSystemsUpdate() {
    for (Components::PlayerComponent& component : Globals::playerComponentList) { component.Move(); }
    for (Components::RigidBodyComponent& component : Globals::rigidBodyComponentList) { component.Move(); }

    m_camera.Update();
    m_mouseRay.UpdateRay();

    Physics::CollisionSystem(m_camera);
}

void Engine::SetMemberVars() {
    Components::PlayerComponent* pComp = Globals::GetPlayerComponent(0);
    if (!pComp) return;

    m_camera.SetParent(Globals::GetEntity(pComp->GetEntityID()));
    m_mouseRay.AttachToPlayer();
}

void Engine::WaterRenderPasses(Rendering::MasterRenderer& renderer, Entities::Camera& camera, Water::WaterFrameBuffer& waterFBOs, std::vector<Water::WaterTile>& waterList) {
    // Reflection pass
    glEnable(GL_CLIP_DISTANCE0);
    waterFBOs.BindReflectionFrameBuffer();
    float distance = 2.0f * (camera.GetPosition().y - waterList[0].GetY());
    camera.SetPositionY(camera.GetPosition().y - distance);
    camera.InvertPitch();
    renderer.RenderScene(Globals::lightComponentList, camera, glm::vec4(0, 1, 0, -waterList[0].GetY() + 0.1));
    camera.SetPositionY(camera.GetPosition().y + distance);
    camera.InvertPitch();

    // Refraction pass
    waterFBOs.BindRefractionFrameBuffer();
    renderer.RenderScene(Globals::lightComponentList, camera, glm::vec4(0, -1, 0, waterList[0].GetY()));

    // Final pass
    waterFBOs.UnbindCurrentFrameBuffer();
    glDisable(GL_CLIP_DISTANCE0); // Some drivers ignore this, an alternative is to set the plane height to really high/low
}

void Engine::MainLoopEnd() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    Rendering::DisplayManager::Update();
}

void Engine::UI_Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
    ImGui_ImplOpenGL3_Init();
}

void Engine::UI_CreateFrames() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // ImGui::ShowDemoWindow(); // Show demo window! :)
}

void Engine::UI_Update() {
    ImGui::GetIO().WantCaptureKeyboard ?
        InputEngine::Input::SetEnabled_Keyboard(false) : InputEngine::Input::SetEnabled_Keyboard(true);
    ImGui::GetIO().WantCaptureMouse ?
        InputEngine::Input::SetEnabled_Mouse(false) : InputEngine::Input::SetEnabled_Mouse(true);

    if (/*Globals::editorSelectedEntity && */Globals::editorShowInspectorMenu) {
        if (!Globals::editorSelectedEntity && !Globals::entityMap.empty()) {
            Globals::editorSelectedEntity = &Globals::entityMap.at(Globals::rigidBodyComponentList.at(0).GetEntityID());
        }

        ImGui::Begin("Inspector");
        ImGui::Text("%s (%d)", Globals::editorSelectedEntity->GetName().c_str(), Globals::editorSelectedEntity->GetID());

        ImGui::InputFloat3("Position", &Globals::entityMap.at(Globals::editorSelectedEntity->GetID()).GetPosition().x, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);
        ImGui::InputFloat3("Rotation", &Globals::entityMap.at(Globals::editorSelectedEntity->GetID()).GetRotation().x, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);

        if ((int)Globals::editorSelectedEntity->GetRigidBodyCompPos() != -1) {
            ImGui::SeparatorText("Rigid body:");
            ImGui::InputFloat3("Velocity", &Globals::rigidBodyComponentList.at(Globals::editorSelectedEntity->GetRigidBodyCompPos()).GetVelocity().x, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::InputFloat3("Acceleration", &Globals::rigidBodyComponentList.at(Globals::editorSelectedEntity->GetRigidBodyCompPos()).GetAcceleration().x, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::InputFloat3("Torque", &Globals::rigidBodyComponentList.at(Globals::editorSelectedEntity->GetRigidBodyCompPos()).GetTorque().x, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);

            ImGui::Spacing(); ImGui::Spacing();

            ImGui::InputFloat("Mass", &Globals::rigidBodyComponentList.at(Globals::editorSelectedEntity->GetRigidBodyCompPos()).GetMass(), 0, 0, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::InputFloat("Friction", &Globals::rigidBodyComponentList.at(Globals::editorSelectedEntity->GetRigidBodyCompPos()).GetFriction(), 0, 0, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::Separator();
        }

        ImGui::End();
    }

    if (Globals::editorShowAddMenu) {
        ImGui::Begin("Add");
        ImGui::InputText("Name", name, 20);
        ImGui::InputText("Model file name", modelPath, 30);
        ImGui::InputText("Texture file name", texturePath, 30);

        if (ImGui::Button("Add")) {
            std::string modelStr = std::string(modelPath);
            std::string textureStr = std::string(texturePath);

            if (!modelStr.empty() && !textureStr.empty() && Rendering::Loader::DoesFileExist("res/models/" + modelStr) && Rendering::Loader::DoesFileExist("res/textures/" + textureStr)) {
                unsigned tmpID = Entities::CreateEntity(
                    name,
                    Models::TexturedModel(
                        Rendering::OBJLoader::LoadOBJModel(modelStr),
                        Textures::ModelTexture(
                            Rendering::Loader::LoadTexture(textureStr), 1, 0, true, true
                        )
                    ),
                    glm::vec3(0, 0, 0)
                );

                Components::CreateComponent(Components::OBB, tmpID);
                Components::CreateComponent(Components::RIGID_BODY, tmpID, 0.1);
            }
        }

        if (ImGui::Button("Save")) {
            Utilities::SaveSystem::Save("scene.json");
        }

        ImGui::End();
    }
}

void Engine::CleanUp(Water::WaterFrameBuffer& waterFBOs, Rendering::MasterRenderer& renderer) {
    // TODO Optimize: Some transform matrices don't need to be calculated every frame
    waterFBOs.CleanUp();
    renderer.CleanUp();
    Rendering::Loader::CleanUp();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    Rendering::DisplayManager::Close();
}
