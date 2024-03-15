#ifndef CAMERA_H
#define CAMERA_H

#include "Engine/ECS/Entities/Entity.hpp"
#include <iostream>

namespace MyEngine {
    namespace Entities {
        class Camera {
            private:
                Entity* m_parent = nullptr;

                glm::vec3 m_position = glm::vec3(0), m_rotation = glm::vec3(0);
                glm::vec2 m_mousePosition = glm::vec2(0), m_mouseDelta = glm::vec2(0);
                glm::vec3 m_fpPos = glm::vec3(0, 2, 1), m_tpPos = glm::vec3(0, 2, -5);

                static bool m_firstPersonToggle;
                static bool m_mouseLocked;

                void Rotate();

            public:
                Camera();

                void Update();
                void UpdateCursor();
                void Move();

                static void ToggleFirstPerson();
                static void ToggleMouseLock();
                static void SetMouseLocked(bool state) { m_mouseLocked = state; }
                void InvertPitch();

                const glm::vec3& GetPosition() const;
                const glm::vec3& GetRotation() const;
                static bool GetMouseLocked() { return m_mouseLocked; }

                void SetParent(Entity* parent) { m_parent = &parent[0]; }
                void SetRotation(glm::vec3 v);
                void SetRotationX(float value);
                void SetPositionY(float y);
        };
    }
}

#endif
