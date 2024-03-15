#include "Engine/ECS/Components/OBBComponent.hpp"
#include "Engine/Globals.hpp"
#include "Engine/Other/Math.hpp"
#include "Engine/ECS/EntityManagement.hpp"

using namespace MyEngine::Components;

OBBComponent::OBBComponent(unsigned entityID, bool debug) : m_entityID(entityID), m_visualDebugging(debug)
{
    GenerateModel();
}

void OBBComponent::GenerateModel()
{
    m_model = Models::TexturedModel(
        Rendering::Loader::GenerateCollider(Globals::entityMap.at(m_entityID).GetModel().GetRawModel().GetExtremes()),
        Globals::textureList.at(2) // TODO: un-hardcode this
    );
}
