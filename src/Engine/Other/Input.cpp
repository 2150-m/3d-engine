#include "Engine/Other/Input.hpp"
#include "Engine/Globals.hpp"
#include "Engine/ECS/Components/PlayerComponent.hpp"
#include "Engine/ECS/Entities/Camera.hpp"
#include "Engine/Rendering/DisplayManager.hpp"
#include "Engine/Other/Settings.hpp"
#include "Engine/Other/Printer.hpp"
#include <asm-generic/errno.h>

namespace MyEngine {
    namespace InputEngine {
        bool Input::m_printInputEvents = false;
        bool Input::m_keyboardEnabled = true;
        bool Input::m_mouseEnabled = true;

        void Input::Init() {
            m_printInputEvents = false;

            glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            glfwSetKeyCallback(glfwGetCurrentContext(), Callback);
            glfwSetMouseButtonCallback(glfwGetCurrentContext(), MouseCallback);
        }

        void Input::MouseCallback(GLFWwindow* window, int button, int action, int mods) {
            if (!m_mouseEnabled) return;

            if (m_printInputEvents) {
                if (action == GLFW_RELEASE)
                    Printer::Print(Printer::OTHER, "Mouse button released. <Input>", glfwGetMouseButton(glfwGetCurrentContext(), button));
                if (action == GLFW_PRESS)
                    Printer::Print(Printer::OTHER, "Mouse button pressed. <Input>", glfwGetMouseButton(glfwGetCurrentContext(), button));
            }

            switch (button) {
                case Settings::btn_MousePrimary: {
                    if (action == GLFW_PRESS) {
                        if (Entities::Camera::GetMouseLocked() && (int)Globals::rayComponentList.at(0).GetCollidingID() != -1) {
                            Globals::editorSelectedEntity = &Globals::entityMap.at(Globals::rayComponentList.at(0).GetCollidingID());
                        }/* else {
                            Globals::editorSelectedEntity = nullptr;
                        }*/
                    }
                    break;
                }
            }
        }

        void Input::Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (!m_keyboardEnabled) return;

            if (m_printInputEvents) {
                if (action == GLFW_RELEASE)
                    Printer::Print(Printer::OTHER, "Key %s released. <Input>", glfwGetKeyName(key, scancode));
                if (action == GLFW_PRESS)
                    Printer::Print(Printer::OTHER, "Key %s pressed. <Input>", glfwGetKeyName(key, scancode));
            }

            switch (key) {
                // PLAYER
                case Settings::key_MoveForward: {
                    if (action == GLFW_PRESS)
                        for (auto& component : Globals::playerComponentList) { component.SetDirection(0, 1); }
                    else if (action == GLFW_RELEASE)
                        for (auto& component : Globals::playerComponentList) { component.SetDirection(0, 0); }
                    break;
                }

                case Settings::key_MoveBackward: {
                    if (action == GLFW_PRESS)
                        for (auto& component : Globals::playerComponentList) { component.SetDirection(1, 1); }
                    else if (action == GLFW_RELEASE)
                        for (auto& component : Globals::playerComponentList) { component.SetDirection(1, 0); }
                    break;
                }

                case Settings::key_MoveLeftward: {
                    if (action == GLFW_PRESS)
                        for (auto& component : Globals::playerComponentList) { component.SetDirection(2, 1); }
                    else if (action == GLFW_RELEASE)
                        for (auto& component : Globals::playerComponentList) { component.SetDirection(2, 0); }
                    break;
                }

                case Settings::key_MoveRightward: {
                    if (action == GLFW_PRESS)
                        for (auto& component : Globals::playerComponentList) { component.SetDirection(3, 1); }
                    else if (action == GLFW_RELEASE)
                        for (auto& component : Globals::playerComponentList) { component.SetDirection(3, 0); }
                    break;
                }

                case Settings::key_Jump: {
                    if (action == GLFW_RELEASE)
                        for (auto& component : Globals::playerComponentList) { component.Jump(); }
                    break;
                }

                case Settings::key_PerspectiveSwitch: {
                    if (action == GLFW_RELEASE) Entities::Camera::ToggleFirstPerson();
                    break;
                }

                // MISC.
                case Settings::key_ToggleMouseLock: {
                    if (action == GLFW_RELEASE /*&& !Globals::editorShowAddMenu*/) {
                        if (glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
                            glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                        else
                            glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

                        Entities::Camera::ToggleMouseLock();
                    }
                    break;
                }

                case Settings::key_ToggleAddMenu: {
                    if (action == GLFW_RELEASE) {
                        // if (glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
                        //     glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                        // else
                        //     glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        //
                        // Entities::Camera::ToggleMouseLock();

                        Globals::editorShowAddMenu = !Globals::editorShowAddMenu;
                    }

                    break;
                }

                case Settings::key_ToggleInspectorMenu: {
                    if (action == GLFW_RELEASE) {
                        Globals::editorShowInspectorMenu = !Globals::editorShowInspectorMenu;
                    }

                    break;
                }

                case Settings::key_Escape: {
                    if (action == GLFW_RELEASE) {
                        Globals::editorShowInspectorMenu == 1 ? Globals::editorShowInspectorMenu = 0 : Globals::editorShowInspectorMenu = 1;
                        Globals::editorShowAddMenu == 1 ? Globals::editorShowAddMenu = 0 : Globals::editorShowAddMenu = 1;

                        if (Entities::Camera::GetMouseLocked()) {
                            Entities::Camera::SetMouseLocked(0);
                            glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                        } else {
                            Entities::Camera::SetMouseLocked(1);
                            glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        }
                    }

                    break;
                }
            }
        }
    }
}

