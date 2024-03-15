#ifndef WATERFRBUFFER_H
#define WATERFRBUFFER_H

#include <glad/glad.h>
#include <GL/gl.h>

namespace MyEngine {
    namespace Water {
        class WaterFrameBuffer {
        public:
            WaterFrameBuffer();

            void CleanUp();

            void BindReflectionFrameBuffer();
            void BindRefractionFrameBuffer();
            void UnbindCurrentFrameBuffer();

            GLuint GetReflectionTexture();
            GLuint GetRefractionTexture();
            GLuint GetRefractionDepthTexture();

        private:
            void InitializeReflectionFrameBuffer();
            void InitializeRefractionFrameBuffer();

            void BindFrameBuffer(GLuint frameBuffer, int width, int height);
            GLuint CreateFrameBuffer();
            GLuint CreateTextureAttachment(int width, int height);
            GLuint CreateDepthTextureAttachment(int width, int height);
            GLuint CreateDepthBufferAttachment(int width, int height);

        protected:
            static const int REFLECTION_WIDTH;
            static const int REFLECTION_HEIGHT;

            static const int REFRACTION_WIDTH;
            static const int REFRACTION_HEIGHT;

        private:
            GLuint reflectionFrameBuffer;
            GLuint reflectionTexture;
            GLuint reflectionDepthBuffer;

            GLuint refractionFrameBuffer;
            GLuint refractionTexture;
            GLuint refractionDepthTexture;
        };
    }
}

#endif
