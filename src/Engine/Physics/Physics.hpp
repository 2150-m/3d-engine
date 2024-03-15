#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/ECS/Components/AABBComponent.hpp"
#include "Engine/ECS/Components/OBBComponent.hpp"
#include "Engine/ECS/Components/RayComponent.hpp"
#include "Engine/ECS/Entities/Camera.hpp"

namespace MyEngine {
    namespace Physics {
        void CollisionSystem(const Entities::Camera& playerCamera);

        struct CollisionInfo {
            Entities::Entity* objectA;
            Entities::Entity* objectB;
            float overlap;
            glm::vec3 normal;
        };

        struct OverlapInfo {
            float overlap;
            glm::vec3 normal;
        };

        void AABBCollision();
        bool CheckCollisionAABB(Components::AABBComponent* compA, Components::AABBComponent* compB);

        void OBBCollision();
        bool CheckCollisionOBB(CollisionInfo& collisionInfo, Components::OBBComponent& compA, Components::OBBComponent& compB);
        OverlapInfo MaxOverlap(const std::array<glm::vec3, 8>& vertsA, const std::array<glm::vec3, 8>& vertsB);
        void SATProjection(const glm::vec3& axis, const std::array<glm::vec3, 8>& corners, float& min, float& max);
        bool IsBetween(float value, float lower, float upper);
        std::array<glm::vec3, 6> CreateNormalsList(const std::array<glm::vec3, 8>& corners);
        template <class T>
        std::array<glm::vec3, 8> CreateVertList(T& box);

        void CollisionResolution(CollisionInfo& collisionInfo);

        void RayCollision(const Entities::Camera& playerCamera);
        template <class T>
        bool CheckRayCollision(Components::RayComponent* ray, T* box, const Entities::Camera& playerCamera);
    }
}

#endif
