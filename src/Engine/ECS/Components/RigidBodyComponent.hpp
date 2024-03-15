#ifndef INCLUDE_RIGIDBODYH
#define INCLUDE_RIGIDBODYH

#include <glm/vec3.hpp>

namespace MyEngine {
    namespace Components {
        class RigidBodyComponent {
        public:
            RigidBodyComponent(unsigned id, float mass);

            void Move();
            void SetVelocity(glm::vec3 direction, float amount);
            void SetAcceleration(glm::vec3 direction, float amount);
            void SetTorque(glm::vec3 direction, float amount);

            void ApplyImpulse(glm::vec3 direction, float amount);

            unsigned GetEntityID() const { return m_entityID; }

            float& GetMass() { return m_mass; }
            float GetMass() const { return m_mass; }
            float& GetFriction() { return m_friction; }

            glm::vec3& GetVelocity() { return m_velocity; }
            glm::vec3& GetAcceleration() { return m_acceleration; }
            glm::vec3& GetTorque() { return m_torque; }

            void SetMass(float m) { m_mass = m; }

        private:
            unsigned m_entityID;

            float m_mass = 1;
            float m_friction = 0.05f;

            glm::vec3 m_velocity = glm::vec3(0);
            glm::vec3 m_acceleration = glm::vec3(0);
            glm::vec3 m_torque = glm::vec3(0);
            glm::vec3 m_impulse = glm::vec3(0);
        };
    }
}

#endif
