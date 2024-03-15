#ifndef WATERTILE_H
#define WATERTILE_H

#include <glm/mat4x4.hpp>

namespace MyEngine {
    namespace Water {
        class WaterTile {
        public:
            WaterTile(float x, float y, float z);

            float GetX();
            float GetY();
            float GetZ();
            const glm::mat4& GetTransformMatrix();

            static const float TILE_SIZE;

        private:
            float m_x, m_y, m_z;
            glm::mat4 m_transformMatrix;
        };
    }
}

#endif
