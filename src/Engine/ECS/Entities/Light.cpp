#include "Engine/ECS/Entities/Light.hpp"
#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/Rendering/Loader.hpp"
#include "Engine/Globals.hpp"

using namespace MyEngine::Entities;

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation) :
			m_position(position), m_color(color), m_attenuation(attenuation) {}

void Light::SetPosition(const glm::vec3& pos) { m_position = pos; }
void Light::SetColor(const glm::vec3& col) { m_color = col; }
