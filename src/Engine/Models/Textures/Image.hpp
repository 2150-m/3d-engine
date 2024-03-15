#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>
#include <GL/gl.h>

namespace MyEngine {
    namespace Textures {
        class Image {
        public:
            Image(int width, int height, unsigned char* data) : m_width(width), m_height(height), m_data(data) {}

            static Image Load(std::string path, bool flipImage);

            void CleanUp();

            int GetWidth() const { return m_width; }
            int GetHeight() const { return m_height; }
            unsigned char* GetData() const { return m_data; }

        private:
            GLsizei m_width, m_height;
            unsigned char* m_data;
        };
    }
}

#endif
