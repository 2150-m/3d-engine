#include "Engine/Models/TexturedModel.hpp"
#include "Engine/Globals.hpp"

using namespace MyEngine::Models;

TexturedModel::TexturedModel(RawModel rawModel, Textures::ModelTexture texture) : m_rawModel(rawModel), m_texture(texture)
{
        Globals::modelList.push_back(*this);
}

TexturedModel::TexturedModel() :
        m_rawModel(Rendering::Loader::LoadToVAO(std::vector<GLfloat>{1}, 1)),
        m_texture(Globals::textureList.at(0))
{
        Globals::modelList.push_back(*this);
}
