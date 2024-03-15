#ifndef LIGHTCOMP_HEADER
#define LIGHTCOMP_HEADER

#include "glm/ext/vector_float3.hpp"
namespace MyEngine {
namespace Components {
class LightComponent {
public:
    LightComponent(unsigned entityID, const glm::vec3& color, const glm::vec3& attenuation);

    unsigned GetEntityID() const { return m_entityID; }
    const glm::vec3& GetColor() const { return m_color; }
    const glm::vec3& GetAttenuation() const { return m_attenuation; }
    void SetColor(const glm::vec3& col) { m_color = col; }
    void SetAttenuation(const glm::vec3& att) { m_attenuation = att; }

private:
    unsigned m_entityID;

    glm::vec3 m_color;
    glm::vec3 m_attenuation;
};
}
}

#endif
