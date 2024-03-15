#include "Engine/Models/Textures/ModelTexture.hpp"
#include "Engine/Globals.hpp"

using namespace MyEngine::Textures;

ModelTexture::ModelTexture(GLuint id, float shineDamp = 1, float reflectivity = 0, bool hasTransparency = false, bool useFakeLighting = false) : m_id(id), m_shineDamper(shineDamp), m_reflectivity(reflectivity), m_hasTransparency(hasTransparency), m_useFakeLighting(useFakeLighting)
{
    Globals::textureList.push_back(*this);
}

GLuint ModelTexture::GetID() const { return m_id; }
