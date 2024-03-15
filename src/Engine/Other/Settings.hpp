#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <glfw/glfw3.h>

namespace MyEngine {
    namespace Settings {
        // APP
        static const int windowWidth = 1280;
        static const int windowHeight = 720;

        // PLAYER
        static const float fov = 70, nearPlane = 0.1f, farPlane = 1000;
        static const float mouseSensitivity = 0.1f;

        static const float gravity = -0.01;

        static const float runSpeed = 0.2, turnSpeed = 3, jumpPower = 0.2;

        // SHADERS
        static const float WAVE_SPEED = 0.0001f;

        // DEBUG
        static const bool DEBUGGING = true;

        // KEY BINDINGS
        // Player
        static const int key_PerspectiveSwitch = GLFW_KEY_P;
        static const int key_MoveForward = GLFW_KEY_W;
        static const int key_MoveBackward = GLFW_KEY_S;
        static const int key_MoveLeftward = GLFW_KEY_A;
        static const int key_MoveRightward = GLFW_KEY_D;
        static const int key_Jump = GLFW_KEY_SPACE;

        static const int btn_MousePrimary = GLFW_MOUSE_BUTTON_LEFT;

        // Misc.
        static const int key_ToggleMouseLock = GLFW_KEY_F1;
        static const int key_ToggleAddMenu = GLFW_KEY_F2;
        static const int key_ToggleInspectorMenu = GLFW_KEY_F3;
        static const int key_Escape = GLFW_KEY_ESCAPE;

    }
}

#endif
