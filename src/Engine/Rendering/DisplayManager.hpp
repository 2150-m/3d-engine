#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "Engine/Other/Settings.hpp"

namespace MyEngine {
    namespace Rendering {
        class DisplayManager {
            private:
                static float m_lastFrameTime;
                static int m_renderedFrames;
                static float m_deltaTime;

                static std::string m_windowTitle;

            public:
                static GLFWwindow* m_window;

                static void Create();
                static void Update();
                static void Close();
                static bool ShouldClose();

                static void UpdateFPS();
                static float GetDeltaTime();
        };
    }
}

#endif
