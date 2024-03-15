#include "Engine/Models/Textures/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace MyEngine {
    using namespace Textures;

    Image Image::Load(std::string path, bool flipImage) {
        GLsizei imageWidth = 0, imageHeight = 0, comp = 0;

        stbi_set_flip_vertically_on_load(flipImage);

        unsigned char* buffer = stbi_load(path.c_str(), &imageWidth, &imageHeight, &comp, STBI_rgb_alpha);
        if (stbi_failure_reason()) {
            std::cout << "Texture " << path << " failed to load.\n";
            exit(1);
        }

        return {imageWidth, imageHeight, buffer};
    }

    void Image::CleanUp() {
        stbi_image_free(m_data);
    }
}
