#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "Engine/Models/RawModel.hpp"
#include "Engine/Models/Textures/ModelTexture.hpp"
#include "Engine/Rendering/Loader.hpp"
#include <vector>

namespace MyEngine {
    namespace Models {
        class TexturedModel {
            private:
                Models::RawModel m_rawModel;
                Textures::ModelTexture m_texture;

            public:
                TexturedModel(RawModel rawModel, Textures::ModelTexture texture);
                TexturedModel();

                const Textures::ModelTexture& GetTexture() const { return m_texture; }
                RawModel& GetRawModel() { return m_rawModel; }
                const RawModel& GetRawModel() const { return m_rawModel; }
        };

    }
}

#endif
