#include <cstdlib>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Engine/Rendering/DisplayManager.hpp"
#include "Engine/Rendering/Loader.hpp"
#include "Engine/Models/Textures/Image.hpp"
#include "Engine/Other/Printer.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <array>
#include <iostream>
#include <fstream>

namespace MyEngine {
    using namespace Rendering;

    std::vector<GLuint> Loader::m_vaoList, Loader::m_vboList, Loader::m_textureList;

    GLuint Loader::CreateVAO() {
        GLuint id;
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
        m_vaoList.push_back(id);
        return id;
    }

    GLuint Loader::CreateVBO(GLenum type) {
        GLuint id;
        glGenBuffers(1, &id);
        glBindBuffer(type, id);
        m_vboList.push_back(id);
        return id;
    }

    void Loader::UnbindVAO() {
        glBindVertexArray(0);
    }

    void Loader::BindIndexBuffer(const std::vector<GLuint>& indices) {
        CreateVBO(GL_ELEMENT_ARRAY_BUFFER);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices.at(0)), indices.data(), GL_STATIC_DRAW);
    }

    Models::RawModel Loader::LoadToVAO(const std::vector<GLfloat> &positions, const std::vector<GLuint> &indices, const std::vector<GLfloat> &texture, const std::vector<GLfloat>& normals, const std::array<glm::vec2, 3>& extremes) {
        GLuint id = CreateVAO();
        BindIndexBuffer(indices);

        StoreInAttributeList(0, 3, positions);
        StoreInAttributeList(1, 2, texture);
        StoreInAttributeList(2, 3, normals);

        UnbindVAO();
        GLuint size = indices.size();
        return { id, size, extremes };
    }

    Models::RawModel Loader::LoadToVAO(const std::vector<GLfloat> &positions, const std::vector<GLuint> &indices, const std::vector<GLfloat> &texture) {
        GLuint id = CreateVAO();
        BindIndexBuffer(indices);

        StoreInAttributeList(0, 3, positions);
        StoreInAttributeList(1, 2, texture);

        UnbindVAO();
        GLuint size = indices.size();
        return { id, size };
    }

    Models::RawModel Loader::LoadToVAO(const std::vector<GLfloat> &positions, int dimensions) {
        GLuint id = CreateVAO();

        StoreInAttributeList(0, dimensions, positions);

        UnbindVAO();
        return { id, (unsigned) positions.size() / dimensions };
    }

    template<typename T>
    void Loader::StoreInAttributeList(int attributeID, int coordCount, const std::vector<T>& data) {
        CreateVBO(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(attributeID, coordCount, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
        glEnableVertexAttribArray(attributeID);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint Loader::LoadTexture(const std::string &fileName) {
        Textures::Image image = Textures::Image::Load("res/textures/" + fileName, true);

        GLuint textureID = 0;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetData());

        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);

        // Anisotropic filtering
        if (glfwExtensionSupported("GL_EXT_texture_filter_anisotropic")) {
            GLfloat maxAmount = 0;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAmount);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAmount);
        } else {
            std::cout << "Anisotropic filtering not supported.\n";
        }

        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindTexture(GL_TEXTURE_2D, 0);

        m_textureList.push_back(textureID);
        image.CleanUp();
        return textureID;
    }

    GLuint Loader::LoadCubeMap(std::vector<std::string> list) {
        GLuint id = 0;
        glGenTextures(1, &id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        for (unsigned long i = 0; i < list.size(); i++) {
            Textures::Image image = Textures::Image::Load("res/textures/skybox/" + list[i], false);

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetData());
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        m_textureList.push_back(id);
        return id;
    }

    bool Loader::DoesFileExist(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file) {
            Printer::PrintError(Printer::OTHER, "Could not find file: %s", fileName.c_str());
            return 0;
        }
        return 1;
    }

    Models::RawModel Loader::GenerateCollider(const std::array<glm::vec2, 3>& extremes) {
        std::vector<GLfloat> positions = {
            extremes[0].y, extremes[1].x, extremes[2].y,
            extremes[0].y, extremes[1].y, extremes[2].y,
            extremes[0].x, extremes[1].y, extremes[2].y,
            extremes[0].x, extremes[1].x, extremes[2].y,

            extremes[0].y, extremes[1].x, extremes[2].x,
            extremes[0].y, extremes[1].y, extremes[2].x,
            extremes[0].x, extremes[1].y, extremes[2].x,
            extremes[0].x, extremes[1].x, extremes[2].x,

            extremes[0].x, extremes[1].x, extremes[2].y,
            extremes[0].x, extremes[1].y, extremes[2].y,
            extremes[0].x, extremes[1].y, extremes[2].x,
            extremes[0].x, extremes[1].x, extremes[2].x,

            extremes[0].y, extremes[1].x, extremes[2].y,
            extremes[0].y, extremes[1].y, extremes[2].y,
            extremes[0].y, extremes[1].y, extremes[2].x,
            extremes[0].y, extremes[1].x, extremes[2].x,

            extremes[0].y, extremes[1].x, extremes[2].x,
            extremes[0].y, extremes[1].x, extremes[2].y,
            extremes[0].x, extremes[1].x, extremes[2].y,
            extremes[0].x, extremes[1].x, extremes[2].x,

            extremes[0].y, extremes[1].y, extremes[2].x,
            extremes[0].y, extremes[1].y, extremes[2].y,
            extremes[0].x, extremes[1].y, extremes[2].y,
            extremes[0].x, extremes[1].y, extremes[2].x
        };

        std::vector<GLuint> indices = {
            0,1,3,
            3,1,2,
            4,5,7,
            7,5,6,
            8,9,11,
            11,9,10,
            12,13,15,
            15,13,14,
            16,17,19,
            19,17,18,
            20,21,23,
            23,21,22
        };

        std::vector<GLfloat> textureCoords = {
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0,
            0,0,
            0,1,
            1,1,
            1,0
        };

        return LoadToVAO(positions, indices, textureCoords);
    }

    void Loader::CleanUp() {
        for (GLuint i : m_vaoList) { glDeleteVertexArrays(1, &i); }
        for (GLuint i : m_vboList) { glDeleteBuffers(1, &i); }
        for (GLuint i : m_textureList) { glDeleteTextures(1, &i); }
    }
}
