#ifndef LOADER_H
#define LOADER_H

#include "Engine/Models/RawModel.hpp"

#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <array>

namespace MyEngine {
    namespace Rendering {
        class Loader {
            private:
                static std::vector<GLuint> m_vaoList, m_vboList, m_textureList;

                static GLuint CreateVAO();
                static GLuint CreateVBO(GLenum type);

                static void BindIndexBuffer(const std::vector<GLuint>& indices);
                static void UnbindVAO();

                template<typename T>
                static void StoreInAttributeList(int attributeID, int coordCount, const std::vector<T>& data);

            public:
                static Models::RawModel LoadToVAO(const std::vector<GLfloat>& positions, const std::vector<GLuint>& indices, const std::vector<GLfloat>& textureCoords, const std::vector<GLfloat>& normals, const std::array<glm::vec2, 3>& extremes);

                static Models::RawModel LoadToVAO(const std::vector<GLfloat> &positions, const std::vector<GLuint> &indices, const std::vector<GLfloat> &texture);

                static Models::RawModel LoadToVAO(const std::vector<GLfloat> &positions, int dimensions);

                static GLuint LoadTexture(const std::string& fileName);
                static GLuint LoadCubeMap(std::vector<std::string> list);
                static Models::RawModel GenerateCollider(const std::array<glm::vec2, 3>& extremes);

                static void CleanUp();

                static bool DoesFileExist(const std::string& file);
        };
    }
}

#endif
