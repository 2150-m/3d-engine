#include "Engine/ECS/Components/AABBComponent.hpp"
#include "Engine/Globals.hpp"
#include "Engine/Other/Math.hpp"
#include "Engine/ECS/EntityManagement.hpp"

using namespace MyEngine::Components;

AABBComponent::AABBComponent(unsigned entityID, bool debug) : m_entityID(entityID), m_visualDebugging(debug)
{
    GenerateModel();
}

void AABBComponent::GenerateModel()
{
    m_model = Models::TexturedModel(
        Rendering::Loader::GenerateCollider(Globals::entityMap.at(m_entityID).GetModel().GetRawModel().GetExtremes()),
        Globals::textureList.at(1) // TODO: un-hardcode this
    );
}

void AABBComponent::RecalculateAABB()
{
    Entities::Entity& entity = *Globals::GetEntity(m_entityID);

    glm::mat4 rotationMat = Other::Maths::CreateRotationMatrix(entity.GetRotation()); // TODO: will non- default scale mess this up?

    std::array<glm::vec2, 3> currentExtremes = entity.GetModel().GetRawModel().GetExtremes();
    std::array<glm::vec2, 3> newExtremes = {glm::vec2(0), glm::vec2(0), glm::vec2(0)};

    // Arvo's method
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float a = rotationMat[i][j] * currentExtremes[j][1];
            float b = rotationMat[i][j] * currentExtremes[j][0];
            newExtremes[i][1] += (a < b ? a : b);
            newExtremes[i][0] += (a < b ? b : a);
        }
    }

    SetModel(
        Models::TexturedModel(
            Rendering::Loader::GenerateCollider(newExtremes),
            Globals::textureList.at(1)
        )
    );
    GetModel().GetRawModel().SetExtremes(newExtremes);
}
