#ifndef PLAYERCOMP
#define PLAYERCOMP

#include "Engine/ECS/Entities/Entity.hpp"
#include <array>
#include <glm/vec3.hpp>

namespace MyEngine {
    namespace Components {
        class PlayerComponent {
            public:
                PlayerComponent(unsigned);

                enum MovementDirection { NONE = 0, FORWARD, BACKWARD, LEFTWARD, RIGHTWARD };

                void Move();
                void Jump();

                void SetDirection(int, int);

                unsigned GetEntityID() const { return m_entityID; }
                const glm::vec3& GetVelocity() const { return m_velocity; }

            private:
                unsigned m_entityID;

                float m_currentSpeed = 0;
                float m_upwardsSpeed = 0;
                float m_directionModifier = 0;

                glm::vec3 m_velocity;

                glm::ivec3 m_dirVec = glm::ivec3(0,0,0);
                std::array<unsigned, 4> m_pressedKeys = {0,0,0,0};

                bool m_isInAir = false;
        };
    }
}

#endif
