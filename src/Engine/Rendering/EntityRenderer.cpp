#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Engine/Rendering/EntityRenderer.hpp"
#include "Engine/Other/Math.hpp"
#include "Engine/Other/Settings.hpp"
#include "Engine/Rendering/MasterRenderer.hpp"
#include "Engine/ECS/Components/AABBComponent.hpp"
#include "Engine/ECS/EntityManagement.hpp"

#include <iostream>
#include <map>
#include <vector>

namespace MyEngine {
    namespace Rendering {
        EntityRenderer::EntityRenderer(Shaders::StaticShader& staticShader, const glm::mat4& projectionMatrix) : m_staticShader(&staticShader) {
            m_staticShader->Start();
            m_staticShader->LoadProjectionMat(projectionMatrix);
            m_staticShader->Stop();
        }

        void EntityRenderer::Render(const std::map<const Models::TexturedModel*, std::vector<const Entities::Entity*>>& entityBatches) {
            for (auto& element : entityBatches) {
                PrepareTexturedModel(*element.first);

                for (auto& entity : element.second) {
                    PrepareInstance(&entity[0]);
                    glDrawElements(GL_TRIANGLES, element.first->GetRawModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
                }

                UnbindTexturedModel();
            }

            // TODO: optimize for batch rendering
            for (Components::AABBComponent comp : Globals::aabbComponentList) {
                PrepareTexturedModel(comp.GetModel());
                PrepareAABB(&comp);
                glDrawElements(GL_TRIANGLES, comp.GetModel().GetRawModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
                UnbindTexturedModel();
            }

            for (Components::OBBComponent comp : Globals::obbComponentList) {
                PrepareTexturedModel(comp.GetModel());
                PrepareOBB(&comp);
                glDrawElements(GL_TRIANGLES, comp.GetModel().GetRawModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
                UnbindTexturedModel();
            }
        }

        void EntityRenderer::PrepareTexturedModel(const Models::TexturedModel& model) {
            glBindVertexArray(model.GetRawModel().GetID());

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            if (model.GetTexture().GetHasTransparency()) { MasterRenderer::DisableCulling(); }

            m_staticShader->LoadUseFakeLighting(model.GetTexture().GetUseFakeLighting());
            m_staticShader->LoadShineVariables(model.GetTexture().GetShineDamper(), model.GetTexture().GetReflectivity());

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, model.GetTexture().GetID());
        }

        void EntityRenderer::UnbindTexturedModel() {
            MasterRenderer::EnableCulling();

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);

            glBindVertexArray(0);
        }

        void EntityRenderer::PrepareInstance(const Entities::Entity* entity) {
            glm::mat4 transformMatrix = Other::Maths::CreateTransformMatrix(entity->GetPosition(), entity->GetRotation(), entity->GetScale());
            m_staticShader->LoadTransformMat(transformMatrix);
            m_staticShader->LoadIsColliding(0); // todo: prevents the entities that are not colliders from being lit up
        }

        void EntityRenderer::PrepareAABB(Components::AABBComponent* comp) {
            Entities::Entity* entity = Globals::GetEntity(comp->GetEntityID());
            glm::mat4 transformMatrix = Other::Maths::CreateTransformMatrix(entity->GetPosition(), glm::vec3(0), entity->GetScale());
            m_staticShader->LoadTransformMat(transformMatrix);
            m_staticShader->LoadIsColliding(comp->IsColliding() && comp->GetVisualDebugging());
        }

        void EntityRenderer::PrepareOBB(Components::OBBComponent* comp) {
            Entities::Entity* entity = Globals::GetEntity(comp->GetEntityID());
            glm::mat4 transformMatrix = Other::Maths::CreateTransformMatrix(entity->GetPosition(), entity->GetRotation(), entity->GetScale());
            m_staticShader->LoadTransformMat(transformMatrix);
            m_staticShader->LoadIsColliding(comp->IsColliding() && comp->GetVisualDebugging());
        }

        // void EntityRenderer::Render(Entities::Entity& entity, Shaders::StaticShader& shader) {
        //     glBindVertexArray(entity->GetModel().GetRawModel().GetID());

        //     glEnableVertexAttribArray(0);
        //     glEnableVertexAttribArray(1);
        //     glEnableVertexAttribArray(2);

        //     glm::mat4 transformMatrix = Other::Maths::CreateTransformMatrix(entity->GetPosition(), entity->GetRotation(), entity->GetScale());
        //     shader.LoadTransformMat(transformMatrix);

        //     shader.LoadShineVariables(entity->GetModel().GetTexture().GetShinedamper(), entity->GetModel().GetTexture().GetReflectivity());

        //     glActiveTexture(GL_TEXTURE0);
        //     glBindTexture(GL_TEXTURE_2D, entity->GetModel().GetTexture().GetID());

        //     glDrawElements(GL_TRIANGLES, entity->GetModel().GetRawModel().GetVertexCount(), GL_UNSIGNED_INT, 0);

        //     glDisableVertexAttribArray(0);
        //     glDisableVertexAttribArray(1);
        //     glDisableVertexAttribArray(2);

        //     glBindVertexArray(0);
        // }
    }
}
