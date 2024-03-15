#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/Shaders/StaticShader.hpp"
#include "Engine/ECS/Components/AABBComponent.hpp"
#include "Engine/ECS/Components/OBBComponent.hpp"

#include <cstdint>
#include <vector>
#include <map>

namespace MyEngine {
    namespace Rendering {
        class EntityRenderer {
            private:
                Shaders::StaticShader* m_staticShader;

            public:
                EntityRenderer(Shaders::StaticShader&, const glm::mat4&);

                void Render(const std::map<const Models::TexturedModel*, std::vector<const Entities::Entity*>>& entities);
                // void Render(Entities::Entity&, Shaders::StaticShader&);

                void PrepareTexturedModel(const Models::TexturedModel&);
                void UnbindTexturedModel();
                void PrepareInstance(const Entities::Entity*);
                void PrepareAABB(Components::AABBComponent* comp);
                void PrepareOBB(Components::OBBComponent* comp);
        };
    }
}

#endif
