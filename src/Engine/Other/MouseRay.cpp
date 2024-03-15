#include "Engine/Other/MouseRay.hpp"
#include "Engine/Other/Math.hpp"
#include "Engine/Other/Settings.hpp"
#include "Engine/Other/Printer.hpp"
#include "Engine/ECS/ComponentManagement.hpp"

namespace MyEngine {
    using namespace Other;

    MouseRay::MouseRay(const Entities::Camera& camera, const glm::mat4& projMat)
        : m_camera(camera), m_projMatrix(projMat), m_viewMatrix(Maths::CreateViewMatrix(m_camera))
    {
    }

    void MouseRay::AttachToPlayer()
    {
        // TODO Hardcoded to the player. Change to camera
        Components::CreateComponent(Components::RAY, Globals::GetPlayerComponent(0)->GetEntityID(), 1);
    }

    void MouseRay::UpdateRay()
    {
        // TODO Disable when controlling the player

        m_viewMatrix = Maths::CreateViewMatrix(m_camera);

        // Conversion: Viewport space -> Normalized device space -> Homogeneous clip space -> Eye space -> World space
        // Norm. device coordinates conversion
        double mouseX, mouseY;
        glfwGetCursorPos(glfwGetCurrentContext(), &mouseX, &mouseY);
        glm::vec2 normalized = Convert_NDeviceSpace(mouseX, mouseY);
        // Clip conversion
        glm::vec4 clip(normalized.x, normalized.y, -1, 1);
        // Eye conversion
        glm::vec4 eye = Convert_EyeSpace(clip);
        // Final world conversion
        m_ray = Convert_WorldSpace(eye);

        for (auto& ray : Globals::rayComponentList)
        {
            // TODO Camera needs to be made into a special entity with its own ID, because this could break if the player has ray comps.
            if (ray.GetEntityID() == Globals::playerComponentList[0].GetEntityID())
            {
                ray.SetRay(m_ray);
                break;
            }
        }
    }

    glm::vec2 MouseRay::Convert_NDeviceSpace(double mouseX, double mouseY)
    {
        return {
            (2 * mouseX) / (float) Settings::windowWidth - 1,
            -((2 * mouseY) / (float) Settings::windowHeight - 1)
        };
    }

    glm::vec4 MouseRay::Convert_EyeSpace(const glm::vec4& clipSpaceVector)
    {
        glm::vec4 eye = glm::inverse(m_projMatrix) * clipSpaceVector;
        eye.z = -1;
        eye.w = 0;
        return eye;
    }

    glm::vec3 MouseRay::Convert_WorldSpace(const glm::vec4& eyeSpaceVector)
    {
        return glm::normalize(glm::vec3(glm::inverse(m_viewMatrix) * eyeSpaceVector));
    }
}
