#include "Engine/Rendering/DisplayManager.hpp"
#include "Engine/ECS/Components/RigidBodyComponent.hpp"
#include <glm/ext/quaternion_geometric.hpp>

#include "Engine/Globals.hpp"

namespace MyEngine {
    namespace Components {
        RigidBodyComponent::RigidBodyComponent(unsigned entityID, float mass)
            : m_entityID(entityID), m_mass(mass)
        {}

        void RigidBodyComponent::Move() {
            m_velocity += m_acceleration * m_mass;
            if (m_impulse.length() > 0) {
                m_velocity += m_impulse;
                m_impulse = glm::vec3(0);
            }
            m_velocity -= m_velocity * m_friction;

            Globals::entityMap.at(m_entityID).IncreasePosition(m_velocity * Rendering::DisplayManager::GetDeltaTime());
            Globals::entityMap.at(m_entityID).IncreaseRotation(m_torque * Rendering::DisplayManager::GetDeltaTime());
        }

        void RigidBodyComponent::ApplyImpulse(glm::vec3 direction, float amount) {
            m_impulse = direction * amount;
        }

        void RigidBodyComponent::SetVelocity(glm::vec3 direction, float value) {
            m_velocity = direction * value;
        }

        void RigidBodyComponent::SetAcceleration(glm::vec3 direction, float value) {
            m_acceleration = direction * value;
        }

        void RigidBodyComponent::SetTorque(glm::vec3 direction, float value) {
            m_torque = direction * value; // Not real torque, I lied
        }
    }
}

