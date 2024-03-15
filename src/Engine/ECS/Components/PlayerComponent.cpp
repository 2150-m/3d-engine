#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Engine/Rendering/DisplayManager.hpp"
#include "Engine/Globals.hpp"
#include "Engine/ECS/Components/PlayerComponent.hpp"
#include "Engine/Other/Printer.hpp"

#include <glm/ext/quaternion_common.hpp>

namespace MyEngine {
    namespace Components {
        PlayerComponent::PlayerComponent(unsigned entityID) : m_entityID(entityID) {}

        void PlayerComponent::Move()
        {
            // for (auto& col : Globals::AABBComponentList)
            // {
            //     if (col.GetEntityID() == m_entityID && col.IsColliding())
            //     {
            //         return;
            //     }
            // }

            m_dirVec = -glm::ivec3(m_pressedKeys[3] - m_pressedKeys[2], 0, m_pressedKeys[1] - m_pressedKeys[0]);

            float sine = -glm::sin(glm::radians(Globals::entityMap.at(m_entityID).GetRotation().y));
            float cosine = glm::cos(glm::radians(Globals::entityMap.at(m_entityID).GetRotation().y));
            float x = m_dirVec.x * cosine - m_dirVec.z * sine;
            float z = m_dirVec.x * sine + m_dirVec.z * cosine;

            m_velocity = glm::vec3(glm::vec3(x, 0, z) * Settings::runSpeed * Rendering::DisplayManager::GetDeltaTime());
            Globals::entityMap.at(m_entityID).IncreasePosition(m_velocity);

            m_upwardsSpeed += Settings::gravity * Rendering::DisplayManager::GetDeltaTime();

            Globals::entityMap.at(m_entityID).IncreasePosition(glm::vec3(0, m_upwardsSpeed * Rendering::DisplayManager::GetDeltaTime(), 0));
            if (Globals::entityMap.at(m_entityID).GetPosition().y < 0)
            {
                m_upwardsSpeed = 0;
                Globals::entityMap.at(m_entityID).SetPositionY(0);
                m_isInAir = false;
            }
        }

        void PlayerComponent::Jump()
        {
            if (!m_isInAir)
            {
                m_upwardsSpeed = Settings::jumpPower;
                m_isInAir = true;
            }
        }

        void PlayerComponent::SetDirection(int index, int state)
        {
            m_pressedKeys[index] = state;
        }
    }
}

