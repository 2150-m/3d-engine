#ifndef LIGHT_H
#define LIGHT_H

#include "Engine/ECS/Entities/Entity.hpp"

namespace MyEngine {
	namespace Entities {
		class Light {
		private:
			glm::vec3 m_position,
					m_color,
					m_attenuation;

		public:
			Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation = glm::vec3(1,0,0));

			const glm::vec3& GetPosition() const { return m_position; }
			const glm::vec3& GetColor() const { return m_color; }
			const glm::vec3& GetAttenuation() const { return m_attenuation; }
			void SetPosition(const glm::vec3& pos);
			void SetColor(const glm::vec3& col);
		};
	}
}

#endif
