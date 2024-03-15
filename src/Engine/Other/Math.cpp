#include "Engine/Other/Math.hpp"
#include "Engine/Rendering/Loader.hpp"
#include <glm/ext/matrix_transform.hpp>

#include <array>
#include <cstddef>

namespace MyEngine {
    using namespace Other;

    glm::mat4 Maths::CreateTransformMatrix(const glm::vec3& translationVec, const glm::vec3& rotationVec, const glm::vec3& scaleVec) {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, translationVec);
        matrix = glm::rotate(matrix, glm::radians(rotationVec.x), glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotationVec.y), glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(rotationVec.z), glm::vec3(0, 0, 1));
        matrix = glm::scale(matrix, scaleVec);
        return matrix;
    }

    glm::mat3 Maths::CreateRotationMatrix(const glm::vec3& rotationVec) {
        glm::mat4 matrix = glm::mat4(1.0f);
        matrix = glm::rotate(matrix, glm::radians(rotationVec.x), glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, glm::radians(rotationVec.y), glm::vec3(0, 1, 0));
        matrix = glm::rotate(matrix, glm::radians(rotationVec.z), glm::vec3(0, 0, 1));
        return matrix;
    }

    glm::mat4 Maths::CreateViewMatrix(const Entities::Camera& camera) {
        glm::mat4 matrix = glm::mat4(1.0f);

        matrix = glm::rotate(matrix, (float) glm::radians(camera.GetRotation().x), glm::vec3(1, 0, 0));
        matrix = glm::rotate(matrix, (float) glm::radians(camera.GetRotation().y), glm::vec3(0, 1, 0));

        glm::vec3 pos = camera.GetPosition();
        matrix = glm::translate(matrix, glm::vec3(-pos.x, -pos.y, -pos.z));
        return matrix;
    }
}
