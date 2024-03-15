#include "Engine/Shaders/Water/WaterFrameBuffer.hpp"

#include <glfw/glfw3.h>
#include "Engine/Rendering/DisplayManager.hpp"

namespace MyEngine {
    using namespace Water;

    const int WaterFrameBuffer::REFLECTION_WIDTH = 320;
    const int WaterFrameBuffer::REFLECTION_HEIGHT = 180;
    const int WaterFrameBuffer::REFRACTION_WIDTH = Settings::windowWidth;
    const int WaterFrameBuffer::REFRACTION_HEIGHT = Settings::windowHeight;

    WaterFrameBuffer::WaterFrameBuffer() {
        InitializeReflectionFrameBuffer();
        InitializeRefractionFrameBuffer();
    }

    void WaterFrameBuffer::CleanUp() {
        glDeleteFramebuffers(1, &reflectionFrameBuffer);
        glDeleteTextures(1, &reflectionTexture);
        glDeleteRenderbuffers(1, &reflectionDepthBuffer);
        glDeleteFramebuffers(1, &refractionFrameBuffer);
        glDeleteTextures(1, &refractionTexture);
        glDeleteTextures(1, &refractionDepthTexture);
    }

    void WaterFrameBuffer::BindReflectionFrameBuffer() {
        BindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
    }

    void WaterFrameBuffer::BindRefractionFrameBuffer() {
        BindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
    }

    void WaterFrameBuffer::UnbindCurrentFrameBuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, Settings::windowWidth, Settings::windowHeight);
    }

    GLuint WaterFrameBuffer::GetReflectionTexture() { return reflectionTexture; }
    GLuint WaterFrameBuffer::GetRefractionTexture() { return refractionTexture; }
    GLuint WaterFrameBuffer::GetRefractionDepthTexture() { return refractionDepthTexture; }

    void WaterFrameBuffer::InitializeReflectionFrameBuffer() {
        reflectionFrameBuffer = CreateFrameBuffer();
        reflectionTexture = CreateTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
        reflectionDepthBuffer = CreateDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
        UnbindCurrentFrameBuffer();
    }

    void WaterFrameBuffer::InitializeRefractionFrameBuffer() {
        refractionFrameBuffer = CreateFrameBuffer();
        refractionTexture = CreateTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
        refractionDepthTexture = CreateDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
        UnbindCurrentFrameBuffer();
    }

    void WaterFrameBuffer::BindFrameBuffer(GLuint frameBuffer, int width, int height) {
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
    }

    GLuint WaterFrameBuffer::CreateFrameBuffer() {
        GLuint buffer;
        glGenFramebuffers(1, &buffer);

        glBindFramebuffer(GL_FRAMEBUFFER, buffer);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);

        return buffer;
    }

    GLuint WaterFrameBuffer::CreateTextureAttachment(int width, int height) {
        GLuint texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (const void*)0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
        return texture;
    }

    GLuint WaterFrameBuffer::CreateDepthTextureAttachment(int width, int height) {
        GLuint texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, (const void*)0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
        return texture;
    }

    GLuint WaterFrameBuffer::CreateDepthBufferAttachment(int width, int height) {
        GLuint buffer;
        glGenRenderbuffers(1, &buffer);

        glBindRenderbuffer(GL_RENDERBUFFER, buffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer);
        return buffer;
    }
}
