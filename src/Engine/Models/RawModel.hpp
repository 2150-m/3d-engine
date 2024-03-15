#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <GL/gl.h>
#include <array>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace MyEngine {
    namespace Models {
        class RawModel {
            private:
                GLuint m_vaoID, m_vertexCount;
                std::array<glm::vec2, 3> m_extremes;
                glm::vec3 m_boundingSizes;

                std::array<glm::vec3, 8> m_vertices;

            public:
                RawModel(GLuint id, GLuint vertexCount, const std::array<glm::vec2, 3>& extremes);
                RawModel(GLuint id, GLuint vertexCount);

                glm::vec3 CalculateBoundingSizes();

                GLuint GetID() const;
                GLuint GetVertexCount() const;
                const std::array<glm::vec2, 3>& GetExtremes() const;
                glm::vec3& GetBoundingSizes();

                void SetExtremes(std::array<glm::vec2, 3> newExtremes);
        };
    }
}

#endif
