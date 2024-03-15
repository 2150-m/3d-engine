#include "Engine/Shaders/ShaderProgram.hpp"
#include "Engine/Other/Printer.hpp"
#include "Engine/Globals.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

namespace MyEngine {
    using namespace Shaders;

    GLuint ShaderProgram::CompileShader(const char* path, GLuint type) {
        std::ifstream file(path);
        std::string contents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        const GLchar* source = contents.c_str();

        GLuint id = glCreateShader(type);
        glShaderSource(id, 1, &source, NULL);
        glCompileShader(id);

        GLint result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            GLint length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*) alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);

            Printer::PrintError(Printer::GRAPHICS, "Failed to compile shader (%s)\t<ShaderProgram>\n%s", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
            glDeleteShader(id);
            exit(EXIT_FAILURE);
        }

        return id;
    }

    GLuint ShaderProgram::CreateShader(const char* vertexPath, const char* fragmentPath) {
        GLuint programID = glCreateProgram();

        Printer::Print(Printer::GRAPHICS, "Compiling shader: %s", vertexPath);
        GLuint vertexID = CompileShader(vertexPath, GL_VERTEX_SHADER);
        Printer::Print(Printer::GRAPHICS, "Compiling shader: %s", fragmentPath);
        GLuint fragmentID = CompileShader(fragmentPath, GL_FRAGMENT_SHADER);

        glAttachShader(programID, vertexID);
        glAttachShader(programID, fragmentID);
        glLinkProgram(programID);
        glValidateProgram(programID);

        glDetachShader(programID, vertexID);
        glDetachShader(programID, fragmentID);
        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);

        return programID;
    }

    ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
        m_id = CreateShader(vertexFile, fragmentFile);
    }

    // ShaderProgram :: ShaderProgram(GLuint id, GLuint vertexID, GLuint fragmentID ) : m_id(id), m_vertexID(vertexID), m_fragmentID(fragmentID) {}

    void ShaderProgram::CleanUp() {
        Stop();
        glDeleteProgram(m_id);
    }


    void ShaderProgram::Start() {
        glUseProgram(m_id);
    }

    void ShaderProgram::Stop() {
        glUseProgram(0);
    }

    void ShaderProgram::BindAttribute(GLuint location, const GLchar* name) {
        glBindAttribLocation(m_id, location, name);
    }

    GLuint ShaderProgram::GetUniformLocation(const GLchar* name) {
        return glGetUniformLocation(m_id, name);
    }

    void ShaderProgram::LoadFloat(GLuint location, GLfloat value) {
        glUniform1f(location, value);
    }

    void ShaderProgram::LoadVector(GLuint location, const glm::vec3& vector) {
        glUniform3f(location, vector.x, vector.y, vector.z);
    }

    void ShaderProgram::LoadVector(GLuint location, const glm::vec4& vector) {
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    }

    void ShaderProgram::LoadBool(GLuint location, bool value) {
        GLfloat toLoad = 0;
        if (value) toLoad = 1;
        glUniform1f(location, toLoad);
    }

    void ShaderProgram::LoadMatrix(GLuint location, const glm::mat4& matrix) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::LoadInt(GLuint location, int value) {
        glUniform1i(location, value);
    }
}
