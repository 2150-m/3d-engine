#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/ext/quaternion_common.hpp>
#include "Engine/Rendering/DisplayManager.hpp"
#include "Engine/Other/Input.hpp"
#include "Engine/Other/Printer.hpp"
#include "Engine/ECS/Components/CameraComponent.hpp"
#include "Engine/Globals.hpp"

using namespace MyEngine::Components;

bool CameraComponent::m_firstPersonToggle = false;
bool CameraComponent::m_mouseLocked = false;

CameraComponent::CameraComponent(unsigned entityID) :
    m_entityID(entityID)
{
}

void CameraComponent::Update() {
    UpdateCursor();

    if (m_entityID == -1) {
        return;
    }

    if (!m_mouseLocked) {
        Rotate();
    }

    Move();
}

void CameraComponent::UpdateCursor() {
    double mouseX, mouseY;
    glfwGetCursorPos(Rendering::DisplayManager::m_window, &mouseX, &mouseY);
    glm::vec2 newPosition = glm::vec2(mouseX, mouseY);

    m_mouseDelta = newPosition - m_mousePosition;
    m_mousePosition = newPosition;
}

void CameraComponent::Move() {
    glm::vec3 pos = m_firstPersonToggle ? m_fpPos : m_tpPos;

    float offsetX = pos.z * glm::sin(glm::radians(Globals::GetEntity(m_entityID)->GetRotation().y));
    float offsetZ = pos.z * glm::cos(glm::radians(Globals::GetEntity(m_entityID)->GetRotation().y));

    m_position = Globals::GetEntity(m_entityID)->GetPosition() + glm::vec3(offsetX, pos.y, offsetZ);
}

void CameraComponent::Rotate() {
    m_rotation.x += m_mouseDelta.y * Settings::mouseSensitivity;
    if (m_rotation.x > 89) m_rotation.x = 89;
    if (m_rotation.x < -89) m_rotation.x = -89;

    m_rotation.y += m_mouseDelta.x * Settings::mouseSensitivity;
    Globals::GetEntity(m_entityID)->SetRotationY(-m_rotation.y + 180);
    if (m_rotation.y >= 360) m_rotation.y = 0;
    if (m_rotation.y <= -360) m_rotation.y = 0;

    m_rotation.z = 0;
}

void CameraComponent::ToggleFirstPerson() {
    m_firstPersonToggle = !m_firstPersonToggle;
    Printer::Print(Printer::OTHER, "First person mode: %s.", m_firstPersonToggle ? "ON" : "OFF");
}

void CameraComponent::ToggleMouseLock() {
    m_mouseLocked = !m_mouseLocked;
    Printer::Print(Printer::OTHER, "Mouse locked: %s.", m_mouseLocked ? "ON" : "OFF");
}

void CameraComponent::InvertPitch() {
    float currentPitch = m_rotation.x;
    SetRotationX(-currentPitch);
}

const glm::vec3& CameraComponent::GetPosition() const { return m_position; }
const glm::vec3& CameraComponent::GetRotation() const { return m_rotation; }
void CameraComponent::SetRotation(glm::vec3 v) { m_rotation = v; }
void CameraComponent::SetRotationX(float value) { m_rotation.x = value; }
void CameraComponent::SetPositionY(float y) { m_position.y = y; }
