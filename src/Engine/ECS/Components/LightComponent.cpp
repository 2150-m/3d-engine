#include "Engine/ECS/Components/LightComponent.hpp"
#include "Engine/Globals.hpp"

using namespace MyEngine::Components;

LightComponent::LightComponent(unsigned entityID, const glm::vec3& color, const glm::vec3& attenuation)
    : m_entityID(entityID), m_color(color), m_attenuation(attenuation)
{
}
