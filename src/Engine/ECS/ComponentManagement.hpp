#ifndef COMPMANAGEMENT
#define COMPMANAGEMENT

#include "Engine/ECS/Components/RigidBodyComponent.hpp"

namespace MyEngine {
    namespace Components {
        enum ComponentTypes { PLAYER_COMPONENT, CAMERA, AABB, OBB, RIGID_BODY, RAY, LIGHT };

        void CreateComponent(ComponentTypes type, unsigned entityID, float fvalue = 0, glm::vec3 vec1 = glm::vec3(1), glm::vec3 vec2 = glm::vec3(1, 0, 0));
        void RemoveComponent(ComponentTypes type, unsigned entityID);

        void CreatePlayerComponent(unsigned entityID);
        void CreateAABBComponent(unsigned entityID);
        void CreateOBBComponent(unsigned entityID);
        void CreateRigidBodyComponent(unsigned entityID, float mass = 0.1);
        void CreateRayComponent(unsigned entityID, float length = 1);
        void CreateCameraComponent(unsigned entityID);
        void CreateLightComponent(unsigned entityID, glm::vec3 color, glm::vec3 attenuation);

        void RemovePlayerComponent(unsigned entityID);
        void RemoveAABBComponent(unsigned entityID);
        void RemoveOBBComponent(unsigned entityID);
        void RemoveRigidBodyComponent(unsigned entityID);
        void RemoveRayComponent(unsigned entityID);
        void RemoveCameraComponent(unsigned entityID);
        void RemoveLightComponent(unsigned entityID);

        RigidBodyComponent* GetRBFromEntity(unsigned id);

        void ReassignPlayerCompIDs();
        void ReassignAABBCompIDs();
        void ReassignOBBCompIDs();
        void ReassignRigidBodyCompIDs();
        void ReassignRayCompIDs();
        void ReassignCameraCompIDs();
        void ReassignLightCompIDs();
    }
}

#endif
