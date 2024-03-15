#ifndef MATHS_H
#define MATHS_H

#include "Engine/ECS/Entities/Camera.hpp"
#include "Engine/Globals.hpp"

#include <glm/mat3x3.hpp>

namespace MyEngine {
    namespace Other {
        class Maths {
            public:
                static glm::mat4 CreateTransformMatrix(const glm::vec3& translationVec, const glm::vec3& rotationVec, const glm::vec3& scaleVec);
                static glm::mat3 CreateRotationMatrix(const glm::vec3& rotationVec);
                static glm::mat4 CreateViewMatrix(const Entities::Camera& camera);
        };
    }
}

#endif
