#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Engine/ECS/Entities/Camera.hpp"
#include "Engine/Rendering/DisplayManager.hpp"
#include "Engine/Other/Input.hpp"
#include "Engine/Other/Printer.hpp"
#include <glm/ext/quaternion_common.hpp>

using namespace MyEngine::Entities;

bool Camera::m_firstPersonToggle = false;
bool Camera::m_mouseLocked = false;

Camera::Camera()
{
}

void Camera::Update() {
    UpdateCursor();

    if (!m_parent)
    {
        return;
    }

    if (!m_mouseLocked)
    {
        Rotate();
    }

    Move();
}

void Camera::UpdateCursor() {
    double mouseX, mouseY;
    glfwGetCursorPos(Rendering::DisplayManager::m_window, &mouseX, &mouseY);
    glm::vec2 newPosition = glm::vec2(mouseX, mouseY);

    m_mouseDelta = newPosition - m_mousePosition;
    m_mousePosition = newPosition;
}

void Camera::Move() {
    glm::vec3 pos = m_firstPersonToggle ? m_fpPos : m_tpPos;

    float offsetX = pos.z * glm::sin(glm::radians(m_parent->GetRotation().y));
    float offsetZ = pos.z * glm::cos(glm::radians(m_parent->GetRotation().y));

    m_position = m_parent->GetPosition() + glm::vec3(offsetX, pos.y, offsetZ);
}

void Camera::Rotate() {
    m_rotation.x += m_mouseDelta.y * Settings::mouseSensitivity;
    if (m_rotation.x > 89) m_rotation.x = 89;
    if (m_rotation.x < -89) m_rotation.x = -89;

    m_rotation.y += m_mouseDelta.x * Settings::mouseSensitivity;
    m_parent->SetRotationY(-m_rotation.y + 180);
    if (m_rotation.y >= 360) m_rotation.y = 0;
    if (m_rotation.y <= -360) m_rotation.y = 0;

    m_rotation.z = 0;
}

void Camera::ToggleFirstPerson() {
    m_firstPersonToggle = !m_firstPersonToggle;
    Printer::Print(Printer::OTHER, "First person mode: %s.", m_firstPersonToggle ? "ON" : "OFF");
}

void Camera::ToggleMouseLock() {
    m_mouseLocked = !m_mouseLocked;
    Printer::Print(Printer::OTHER, "Mouse locked: %s.", m_mouseLocked ? "ON" : "OFF");
}

void Camera::InvertPitch() {
    float currentPitch = m_rotation.x;
    SetRotationX(-currentPitch);
}

const glm::vec3& Camera::GetPosition() const { return m_position; }
const glm::vec3& Camera::GetRotation() const { return m_rotation; }
void Camera::SetRotation(glm::vec3 v) { m_rotation = v; }
void Camera::SetRotationX(float value) { m_rotation.x = value; }
void Camera::SetPositionY(float y) { m_position.y = y; }
