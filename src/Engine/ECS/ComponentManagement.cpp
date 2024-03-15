#include "Engine/ECS/ComponentManagement.hpp"
#include "Engine/Globals.hpp"
#include "Engine/ECS/Components/AABBComponent.hpp"
#include "Engine/ECS/Components/PlayerComponent.hpp"
#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/ECS/EntityManagement.hpp"
#include "Engine/Other/Printer.hpp"
#include "Engine/Other/Settings.hpp"
#include <vector>
#include <iostream>

namespace MyEngine {
    namespace Components {

        void CreateComponent(ComponentTypes type, unsigned entityID, float fvalue, glm::vec3 vec1, glm::vec3 vec2) {
            switch (type) {
                case PLAYER_COMPONENT: {
                    CreatePlayerComponent(entityID);
                    break;
                }

                case AABB: {
                    CreateAABBComponent(entityID);
                    break;
                }

                case OBB:
                    CreateOBBComponent(entityID);
                    break;

                case RIGID_BODY: {
                    CreateRigidBodyComponent(entityID, fvalue);
                    break;
                }

                case RAY: {
                    if (fvalue > 0) CreateRayComponent(entityID, fvalue);
                    else            CreateRayComponent(entityID);
                    break;
                }

                case CAMERA: {
                    CreateCameraComponent(entityID);
                    break;
                }

                case LIGHT: {
                    CreateLightComponent(entityID, vec1, vec2);
                    break;
                }
            }
        }

        void RemoveComponent(ComponentTypes type, unsigned entityID) {
            switch (type) {
                case PLAYER_COMPONENT: {
                    RemovePlayerComponent(entityID);
                    break;
                }

                case AABB: {
                    RemoveAABBComponent(entityID);
                    break;
                }

                case OBB: {
                    RemoveOBBComponent(entityID);
                    break;
                }

                case RIGID_BODY: {
                    RemoveRigidBodyComponent(entityID);
                    break;
                }

                case RAY: {
                    RemoveRayComponent(entityID);
                    break;
                }

                case CAMERA: {
                    RemoveCameraComponent(entityID);
                    break;
                }

                case LIGHT: {
                    RemoveLightComponent(entityID);
                    break;
                }
            }
        }

        void CreatePlayerComponent(unsigned entityID) {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            if ((int)entity->GetPlayerCompPos() != -1) {
                Printer::PrintError(Printer::ECS, "[%d, %s]: Already has a PlayerComponent.", entityID, entity->GetName().c_str());
                return;
            }

            Globals::playerComponentList.push_back(Components::PlayerComponent(entityID));
            entity->SetPlayerCompPos(Globals::playerComponentList.size() - 1);
            Printer::Print(Printer::ECS, "[%d, %s]: PlayerComponent added.", entityID, entity->GetName().c_str());
        }

        void RemovePlayerComponent(unsigned entityID) {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            std::vector<Components::PlayerComponent>::iterator it;
            for (it = Globals::playerComponentList.begin(); it != Globals::playerComponentList.end(); it++)
            {
                if (entityID != it->GetEntityID()) continue;
                // TODO: going to need an addtiional unique component id if multiple components of the same type are allowed
                Globals::playerComponentList.erase(it);

                Printer::Print(Printer::ECS, "[%d, %s]: PlayerComponent removed.", entityID, entity->GetName().c_str());

                break;
            }
            entity->SetPlayerCompPos(-1);

            ReassignPlayerCompIDs();
        }

        void CreateAABBComponent(unsigned entityID) {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            if ((int)entity->GetAABBCompPos() != -1)
            {
                Printer::PrintError(Printer::ECS, "[%d, %s]: Already has an AABBComponent.", entityID, entity->GetName().c_str());
                return;
            }

            Globals::aabbComponentList.push_back(Components::AABBComponent(entityID, Settings::DEBUGGING));
            entity->SetAABBCompPos(Globals::aabbComponentList.size() - 1);
            Printer::Print(Printer::ECS, "[%d, %s]: AABBComponent added.", entityID, entity->GetName().c_str());
        }

        void RemoveAABBComponent(unsigned entityID) {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            std::vector<Components::AABBComponent>::iterator it;
            for (it = Globals::aabbComponentList.begin(); it != Globals::aabbComponentList.end(); it++)
            {
                if (entityID != it->GetEntityID()) continue;
                // TODO: going to need an addtiional unique component id if multiple components of the same type are allowed
                Globals::aabbComponentList.erase(it);

                Printer::Print(Printer::ECS, "[%d, %s]: AABBComponent removed.", entityID, entity->GetName().c_str());

                break;
            }
            entity->SetAABBCompPos(-1);

            ReassignAABBCompIDs();
        }

        void CreateOBBComponent(unsigned entityID)
        {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            if ((int)entity->GetOBBCompPos() != -1)
            {
                Printer::PrintError(Printer::ECS, "[%d, %s]: Already has an OBBComponent.", entityID, entity->GetName().c_str());
                return;
            }

            Globals::obbComponentList.push_back(Components::OBBComponent(entityID, Settings::DEBUGGING));
            entity->SetOBBCompPos(Globals::obbComponentList.size() - 1);
            Printer::Print(Printer::ECS, "[%d, %s]: OBBComponent added.", entityID, entity->GetName().c_str());
        }

        void RemoveOBBComponent(unsigned entityID)
        {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            std::vector<Components::OBBComponent>::iterator it;
            for (it = Globals::obbComponentList.begin(); it != Globals::obbComponentList.end(); it++)
            {
                if (entityID != it->GetEntityID()) continue;
                // TODO: going to need an addtiional unique component id if multiple components of the same type are allowed
                Globals::obbComponentList.erase(it);

                Printer::Print(Printer::ECS, "[%d, %s]: OBBComponent removed.", entityID, entity->GetName().c_str());

                break;
            }
            entity->SetOBBCompPos(-1);

            ReassignOBBCompIDs();
        }

        void CreateRigidBodyComponent(unsigned entityID, float mass)
        {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            if ((int)entity->GetRigidBodyCompPos() != -1)
            {
                Printer::PrintError(Printer::ECS, "[%d, %s]: Already has a RigidBodyComponent.", entityID, entity->GetName().c_str());
                return;
            }

            Globals::rigidBodyComponentList.push_back(Components::RigidBodyComponent(entityID, mass));
            entity->SetRigidBodyCompPos(Globals::rigidBodyComponentList.size() - 1);
            Printer::Print(Printer::ECS, "[%d, %s]: RigidBodyComponent added (mass = %.2f).", entityID, entity->GetName().c_str(), mass);
        }

        void RemoveRigidBodyComponent(unsigned entityID)
        {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            std::vector<Components::RigidBodyComponent>::iterator it;
            for (it = Globals::rigidBodyComponentList.begin(); it != Globals::rigidBodyComponentList.end(); it++)
            {
                if (entityID != it->GetEntityID()) continue;
                // TODO: going to need an addtiional unique component id if multiple components of the same type are allowed
                Globals::rigidBodyComponentList.erase(it);

                Printer::Print(Printer::ECS, "[%d, %s]: RigidBodyComponent removed.", entityID, entity->GetName().c_str());

                break;
            }
            entity->SetRigidBodyCompPos(-1);

            ReassignRigidBodyCompIDs();
        }

        void CreateLightComponent(unsigned entityID, glm::vec3 color, glm::vec3 attenuation) {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            if ((int)entity->GetLightCompPos() != -1) {
                Printer::PrintError(Printer::ECS, "[%d, %s]: Already has a LightComponent.", entityID, entity->GetName().c_str());
                return;
            }

            Globals::lightComponentList.push_back(Components::LightComponent(entityID, color, attenuation));
            entity->SetLightCompPos(Globals::lightComponentList.size() - 1);
            Printer::Print(Printer::ECS,
                           "[%d, %s]: LightComponent added (color = (%.2f, %.2f, %.2f), attenuation = (%.2f, %.2f, %.2f)).",
                           entityID, entity->GetName().c_str(),
                           color.x, color.y, color.z, attenuation.x, attenuation.y, attenuation.z
            );
        }

        void RemoveLightComponent(unsigned entityID) {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            std::vector<Components::LightComponent>::iterator it;
            for (it = Globals::lightComponentList.begin(); it != Globals::lightComponentList.end(); it++) {
                if (entityID != it->GetEntityID()) continue;

                Globals::lightComponentList.erase(it);
                Printer::Print(Printer::ECS, "[%d, %s]: LightComponent removed.", entityID, entity->GetName().c_str());
                break;
            }
            entity->SetLightCompPos(-1);

            ReassignLightCompIDs();
        }

        void CreateRayComponent(unsigned entityID, float length)
        {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            Globals::rayComponentList.push_back(Components::RayComponent(entityID, length));
            Printer::Print(Printer::ECS, "[%d, %s]: RayComponent added (length = %.2f).", entityID, entity->GetName().c_str(), length);
        }

        void RemoveRayComponent(unsigned entityID)
        {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            std::vector<Components::RayComponent>::iterator it;
            for (it = Globals::rayComponentList.begin(); it != Globals::rayComponentList.end(); it++)
            {
                if (entityID != it->GetEntityID()) continue;
                Globals::rayComponentList.erase(it);

                Printer::Print(Printer::ECS, "[%d, %s]: RayComponent removed.", entityID, entity->GetName().c_str());

                break;
            }

            //TODO: reassigning
        }

        void CreateCameraComponent(unsigned entityID)
        {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            if ((int)entity->GetCameraCompPos() != -1)
            {
                Printer::PrintError(Printer::ECS, "[%d, %s]: Already has an CameraComponent.", entityID, entity->GetName().c_str());
                return;
            }

            Globals::cameraComponentList.push_back(Components::CameraComponent(entityID));
            entity->SetCameraCompPos(Globals::cameraComponentList.size() - 1);
            Printer::Print(Printer::ECS, "[%d, %s]: CameraComponent added.", entityID, entity->GetName().c_str());
        }

        void RemoveCameraComponent(unsigned entityID)
        {
            Entities::Entity* entity = Globals::GetEntity(entityID);
            if (entity == nullptr) return;

            std::vector<Components::CameraComponent>::iterator it;
            for (it = Globals::cameraComponentList.begin(); it != Globals::cameraComponentList.end(); it++)
            {
                if (entityID != it->GetEntityID()) continue;
                // TODO: going to need an addtiional unique component id if multiple components of the same type are allowed
                Globals::cameraComponentList.erase(it);

                Printer::Print(Printer::ECS, "[%d, %s]: CameraComponent removed.", entityID, entity->GetName().c_str());

                break;
            }
            entity->SetCameraCompPos(-1);

            ReassignCameraCompIDs();
        }

        void ReassignCameraCompIDs()
        {
            for (auto& entity : Globals::entityMap)
            {
                if ((int) entity.second.GetCameraCompPos() == -1)
                    continue;

                for (unsigned i = 0; i < Globals::cameraComponentList.size(); i++)
                {
                    if (Globals::cameraComponentList[i].GetEntityID() != entity.second.GetID())
                        continue;

                    entity.second.SetCameraCompPos(i);
                    break;
                }
            }
        }

        void ReassignPlayerCompIDs()
        {
            for (auto& entity : Globals::entityMap)
            {
                if (entity.second.GetPlayerCompPos() == (unsigned) -1)
                    continue;

                for (unsigned i = 0; i < Globals::playerComponentList.size(); i++)
                {
                    if (Globals::playerComponentList[i].GetEntityID() != entity.second.GetID())
                        continue;

                    entity.second.SetPlayerCompPos(i);
                    break;
                }
            }
        }

        void ReassignAABBCompIDs()
        {
            for (auto& entity : Globals::entityMap)
            {
                if (entity.second.GetAABBCompPos() == (unsigned) -1)
                    continue;

                for (unsigned i = 0; i < Globals::aabbComponentList.size(); i++)
                {
                    if (Globals::aabbComponentList[i].GetEntityID() != entity.second.GetID())
                        continue;

                    entity.second.SetAABBCompPos(i);
                    break;
                }
            }
        }

        void ReassignOBBCompIDs()
        {
            for (auto& entity : Globals::entityMap)
            {
                if (entity.second.GetOBBCompPos() == (unsigned) -1)
                    continue;

                for (unsigned i = 0; i < Globals::obbComponentList.size(); i++)
                {
                    if (Globals::obbComponentList[i].GetEntityID() != entity.second.GetID())
                        continue;

                    entity.second.SetOBBCompPos(i);
                    break;
                }
            }
        }

        void ReassignRigidBodyCompIDs()
        {
            for (auto& entity : Globals::entityMap)
            {
                if (entity.second.GetRigidBodyCompPos() == (unsigned)-1)
                    continue;

                for (unsigned i = 0; i < Globals::rigidBodyComponentList.size(); i++)
                {
                    if (Globals::rigidBodyComponentList[i].GetEntityID() != entity.second.GetID())
                        continue;

                    entity.second.SetRigidBodyCompPos(i);
                    break;
                }
            }
        }

        void ReassignLightCompIDs() {
            for (auto& entity : Globals::entityMap) {
                if ((int)entity.second.GetLightCompPos() == -1)
                    continue;

                for (unsigned i = 0; i < Globals::lightComponentList.size(); i++) {
                    if (Globals::lightComponentList[i].GetEntityID() != entity.second.GetID())
                        continue;

                    entity.second.SetLightCompPos(i);
                    break;
                }
            }
        }

        RigidBodyComponent* GetRBFromEntity(unsigned id)
        {
            for (RigidBodyComponent& rb : Globals::rigidBodyComponentList)
            {
                if (rb.GetEntityID() == id) return &rb;
            }

            return nullptr;
        }
    }

}
