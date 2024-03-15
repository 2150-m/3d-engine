#ifndef CAMERACOMPONENT_INCLUDE
#define CAMERACOMPONENT_INCLUDE

#include "Engine/ECS/Entities/Entity.hpp"

namespace MyEngine {
    namespace Components {
        class CameraComponent {
            public:
                CameraComponent(unsigned entityID);

                void Update();
                void UpdateCursor();
                void Move();

                static void ToggleFirstPerson();
                static void ToggleMouseLock();
                void InvertPitch();

                unsigned GetEntityID() const { return m_entityID; }
                const glm::vec3& GetPosition() const;
                const glm::vec3& GetRotation() const;
                static bool GetMouseLocked() { return m_mouseLocked; }

                // void SetParent(Entities::Entity* parent) { m_parent = &parent[0]; }
                void SetRotation(glm::vec3 v);
                void SetRotationX(float value);
                void SetPositionY(float y);

            private:
                unsigned m_entityID = -1;

                glm::vec3 m_position = glm::vec3(0), m_rotation = glm::vec3(0);
                glm::vec2 m_mousePosition = glm::vec2(0), m_mouseDelta = glm::vec2(0);
                glm::vec3 m_fpPos = glm::vec3(0, 2, 1), m_tpPos = glm::vec3(0, 2, -5);

                static bool m_firstPersonToggle;
                static bool m_mouseLocked;

                void Rotate();
        };
    }
}

#endif
