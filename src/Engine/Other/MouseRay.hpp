#ifndef MOUSERAY_H
#define MOUSERAY_H

#include <glm/mat4x4.hpp>
#include "Engine/ECS/Entities/Camera.hpp"

namespace MyEngine {
    namespace Other {
        class MouseRay {
        public:
            MouseRay(const Entities::Camera& camera, const glm::mat4& projMat);

            void AttachToPlayer();
            void UpdateRay();

            glm::vec3 GetRay() { return m_ray; }

        private:
            glm::vec2 Convert_NDeviceSpace(double mouseX, double mouseY);
            glm::vec4 Convert_EyeSpace(const glm::vec4& clipSpaceVector);
            glm::vec3 Convert_WorldSpace(const glm::vec4& eyeSpaceVector);

            const Entities::Camera& m_camera;
            glm::vec3 m_ray;
            glm::mat4 m_projMatrix;
            glm::mat4 m_viewMatrix;
        };
    }
}

#endif
