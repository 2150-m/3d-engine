#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace MyEngine {
    namespace Shaders {
        class ShaderProgram {
            private:
                GLuint m_id = 0, m_vertexID = 0, m_fragmentID = 0;

                GLuint CompileShader(const char* source, GLuint type);
                GLuint CreateShader(const char* vertexShader, const char* fragmentShader);

            protected:
                virtual void BindAttributes() = 0;
                void BindAttribute(GLuint, const GLchar*);

                GLuint GetUniformLocation(const GLchar* name);
                virtual void GetAllUniformLocations() = 0;

                void LoadFloat(GLuint location, GLfloat value);
                void LoadVector(GLuint location, const glm::vec3& vector);
                void LoadVector(GLuint location, const glm::vec4& vector);
                void LoadBool(GLuint location, bool value);
                void LoadMatrix(GLuint location, const glm::mat4& matrix);
                void LoadInt(GLuint location, int value);

            public:
                ShaderProgram(const char*, const char*);
                ShaderProgram(GLuint, GLuint, GLuint);

                void CleanUp();
                void Start();
                void Stop();
        };
    }
}

#endif
