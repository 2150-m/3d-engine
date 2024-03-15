#include "Engine/Rendering/DisplayManager.hpp"
#include <array>
#include <cstdio>
#include <string>
#include <string_view>
#include <charconv>

namespace MyEngine {
    using namespace Rendering;

    void APIENTRY GLDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
    {
        (void)source;
        (void)id;
        (void)length;
        (void)userParam;

        if (type == GL_DEBUG_TYPE_ERROR)
        {
            std::fprintf(stderr, "%s type: 0x%x\n - severity: 0x%x\n - message: %s\n", (type == GL_DEBUG_TYPE_ERROR ? "\n******** [GL ERROR] ********\n -" : "[GL CALLBACK]\n -" ), type, severity, message);
        }
    }

    GLFWwindow* DisplayManager::m_window = NULL;
    std::string DisplayManager:: m_windowTitle = "App";

    float DisplayManager::m_lastFrameTime = 0;
    int DisplayManager::m_renderedFrames = 0;
    float DisplayManager::m_deltaTime = 1;

    void DisplayManager::Create()
    {
        if (!glfwInit()) { std::cout << "Could not initialize GLFW.\n"; exit(EXIT_FAILURE); }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 8);

        m_window = glfwCreateWindow(Settings::windowWidth, Settings::windowHeight, m_windowTitle.c_str(), NULL, NULL);
        while (!m_window)
        {
            std::cout << "Could not create the window.\n";
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(m_window);
        gladLoadGL();

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebug, nullptr);

        glViewport(0, 0, Settings::windowWidth, Settings::windowHeight);
        glfwSwapInterval(1);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glEnable(GL_MULTISAMPLE);
    }

    void DisplayManager::Update()
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
        UpdateFPS();
    }

    // Credit: tsreaper/simple-game-render-engine
    void DisplayManager::UpdateFPS()
    {
        m_renderedFrames++;

        float currentFrameTime = glfwGetTime(); // in seconds
        if (currentFrameTime - m_lastFrameTime >= 1)
        {
            m_deltaTime = currentFrameTime - m_lastFrameTime;

            float fps = m_renderedFrames / m_deltaTime;

            std::string str = std::to_string(fps);

            glfwSetWindowTitle(m_window, (m_windowTitle + " - FPS: " + str[0]+str[1]+str[2]+str[3]+str[4]).c_str());

            m_lastFrameTime = currentFrameTime;
            m_renderedFrames = 0;
        }
    }

    void DisplayManager::Close() { glfwTerminate(); }

    bool DisplayManager::ShouldClose() { return glfwWindowShouldClose(m_window); }

    float DisplayManager::GetDeltaTime() { return m_deltaTime; }
}
