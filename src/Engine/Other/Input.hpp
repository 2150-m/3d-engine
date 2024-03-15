#ifndef INPUTHEADER
#define INPUTHEADER

#include "Engine/Rendering/DisplayManager.hpp"

// TODO: Replace with a proper event system?
namespace MyEngine {
    namespace InputEngine {
        class Input {
        public:
            static void Init();
            static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void MouseCallback(GLFWwindow* window, int button, int action, int mods);

            static bool IsEnabled_Keyboard() { return m_keyboardEnabled; }
            static void SetEnabled_Keyboard(bool state) { m_keyboardEnabled = state; }
            static bool IsEnabled_Mouse() { return m_mouseEnabled; }
            static void SetEnabled_Mouse(bool state) { m_mouseEnabled = state; }

            static bool m_printInputEvents;
            static bool m_keyboardEnabled;
            static bool m_mouseEnabled;
        };
    }
}

#endif
