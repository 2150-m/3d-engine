#ifndef RAYCOMP_H
#define RAYCOMP_H

#include <glm/vec3.hpp>
#include "Engine/Models/TexturedModel.hpp"

namespace MyEngine {
    namespace Components {
        class RayComponent {
        public:
            RayComponent(unsigned entityID, float length = 1, bool debug = false);

            unsigned GetEntityID() { return m_entityID; }
            unsigned GetCollidingID() { return m_collidingID; }
            const glm::vec3& GetRay() { return m_ray; }
            float GetLength() { return m_length; }

            void SetCollidingID(unsigned id) { m_collidingID = id; }
            void SetRay(glm::vec3 ray) { m_ray = ray; }

        private:
            unsigned m_entityID;
            unsigned m_collidingID = -1;

            glm::vec3 m_ray;
            float m_length = 1;
            // Models::TexturedModel m_model;

            bool m_visualDebugging = false;
        };
    }
}

#endif
