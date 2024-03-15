#include "Engine/ECS/Entities/Entity.hpp"
#include "Engine/Globals.hpp"
#include "Engine/Rendering/Loader.hpp"
#include "Engine/ECS/EntityManagement.hpp"
#include "Engine/Other/Printer.hpp"
#include <glm/glm.hpp>

#include <climits>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace MyEngine {
    namespace Entities {
        Entity::Entity(unsigned id, Models::TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
            m_id(id), m_parentID(-1), m_childrenIDs(),
            m_name(GenerateName()),
            m_model(model),
            m_position(position), m_rotation(rotation), m_scale(scale)
        {
            Printer::Print(Printer::ECS, "Entity created [id: %d, name: %s].", GetID(), GetName().c_str());
        }

        Entity::Entity(unsigned id, std::string name, Models::TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
            m_id(id), m_parentID(-1), m_childrenIDs(),
            m_name(name),
            m_model(model),
            m_position(position), m_rotation(rotation), m_scale(scale)
        {
            Printer::Print(Printer::ECS, "Entity created [id: %d, name: %s].", GetID(), GetName().c_str());
        }

        Entity::~Entity() {
            Printer::Print(Printer::ECS, "Destroying entity [id: %d, name: %s].", GetID(), GetName().c_str());

            if (Globals::entityMap.find(m_parentID) != Globals::entityMap.end()) {
                Entity* parent = &Globals::entityMap.at(m_parentID);

                std::vector<unsigned>& children = parent->GetChildrenIDs();
                for (std::vector<unsigned>::iterator it = children.begin(); it != children.end(); it++) {
                    if (*it == GetID()) {
                        children.erase(it);
                        break;
                    }
                }
            }
        }

        // unsigned Entity::GenerateID() {
        //     int num = 0;
        //     while (Globals::entityMap.count(num) > 0) { num++; }
        //     return num;
        // }

        std::string Entity::GenerateName() {
            return "entity_id" + std::to_string(m_id);
        }

        void Entity::IncreasePosition(const glm::vec3& change) {
            if (m_isMovable) { m_position += change; }
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentPosition(); }
        }

        void Entity::IncreaseRotation(glm::vec3 change) {
            if (m_isRotatable)
            {
                for (int axis = 0; axis < 3; axis++)
                {
                    if (m_rotation[axis] + change[axis] >= 360)
                    {
                        float neededUntilCap = 360 - m_rotation[axis];
                        change[axis] -= neededUntilCap;
                        m_rotation[axis] = 0;
                    }
                    else if (m_rotation[axis] + change[axis] < 0)
                    {
                        change[axis] -= m_rotation[axis];
                        m_rotation[axis] = 360;
                    }
                }

                m_rotation += change;
            }
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentRotation(); }
        }

        void Entity::IncreaseScale(const glm::vec3& change) {
            if (m_isScalable) { m_scale += change; }
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentScale(); }
        }

        void Entity::SetPosition(glm::vec3 vec) {
            m_position = vec;
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentPosition(); }
        }

        void Entity::SetRotation(glm::vec3 vec) {
            m_rotation = vec;
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentRotation(); }
        }

        void Entity::SetPositionX(float value) {
            m_position.x = value;
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentPosition(); }
        }

        void Entity::SetPositionY(float value) {
            m_position.y = value;
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentPosition(); }
        }

        void Entity::SetPositionZ(float value) {
            m_position.z = value;
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentPosition(); }
        }

        void Entity::SetRotationX(float value) {
            m_rotation.x = value;
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentRotation(); }
        }

        void Entity::SetRotationY(float value) {
            m_rotation.y = value;
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentRotation(); }
        }

        void Entity::SetRotationZ(float value) {
            m_rotation.z = value;
            for (long id : m_childrenIDs) { Globals::entityMap.at(id).FollowParentRotation(); }
        }

        void Entity::FollowParentPosition(glm::vec3 offset) {
            if (m_isFollowingPosition) { m_position = Globals::entityMap.at(GetParentID()).GetPosition() + offset; }
        }

        void Entity::FollowParentRotation() {
            if (m_isFollowingRotation) { m_rotation = Globals::entityMap.at(GetParentID()).GetRotation(); }
        }

        void Entity::FollowParentScale() {
            if (m_isFollowingScale) { m_scale = Globals::entityMap.at(GetParentID()).GetScale(); }
        }

        // template <typename T>
        // void Entity::AddChild(T& entity) {
        //     if (entity.HasParent()) {
        //         Printer::PrintError(Printer::ECS, "Entity [id: %d, name: %s] already has a parent: [id: %d, name: %s] ", entity.GetID(), entity.GetName(), GetParentID(), Globals::entityMap.at(GetParentID()).GetName());
        //         return;
        //     }
        //
        //     m_childrenIDs.push_back(entity.GetID());
        //     entity.SetParentID(m_id);
        // }
        //
        // void Entity::AddChild(float id) {
        //     if (Globals::entityMap.at(id).HasParent()) {
        //
        //         Printer::PrintError(Printer::ECS, "Entity [id: %d, name: %s] already has a parent: [id: %d, name: %s] ", entity.GetID(), Globals::entityMap.at(id).GetName(), GetParentID(), Globals::entityMap.at(GetParentID()).GetName());
        //         return;
        //     }
        //
        //     m_childrenIDs.push_back(Globals::entityMap.at(id).GetID());
        //     Globals::entityMap.at(id).SetParentID(m_id);
        // }

        bool Entity::HasParent() { return m_parentID != -1 && Globals::entityMap.count(m_parentID); }
    }
}

