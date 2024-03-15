#include "Engine/Shaders/Water/WaterTile.hpp"
#include "Engine/Other/Math.hpp"

namespace MyEngine {
    using namespace Water;

    const float WaterTile::TILE_SIZE = 150;

    WaterTile::WaterTile(float x, float y, float z) :
            m_x(x), m_y(y), m_z(z),
            m_transformMatrix(Other::Maths::CreateTransformMatrix(
                glm::vec3(m_x, m_y, m_z), glm::vec3(0), glm::vec3(TILE_SIZE)
            ))
    {}

    float WaterTile::GetX() { return m_x; }
    float WaterTile::GetY() { return m_y; }
    float WaterTile::GetZ() { return m_z; }
    const glm::mat4& WaterTile::GetTransformMatrix() { return m_transformMatrix; }
}
