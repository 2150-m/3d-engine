#ifndef ENTITY_H
#define ENTITY_H

#include "Engine/Models/TexturedModel.hpp"

#include <climits>
#include <glm/vec3.hpp>
#include <memory>
#include <string>
#include <vector>

namespace MyEngine {
namespace Entities {
class Entity {
    public:
        // Entity();
        Entity(unsigned id, Models::TexturedModel model, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
        Entity(unsigned id, std::string name, Models::TexturedModel model, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
        ~Entity();

        // TODO: implement active component tracking

        unsigned GenerateID();
        std::string GenerateName();
        // Entity GenerateAABB(const Textures::ModelTexture& texture);
        // Entity GenerateOBB(const Textures::ModelTexture& texture);

        void IncreasePosition(const glm::vec3& change);
        void IncreaseRotation(glm::vec3 change);
        void IncreaseScale(const glm::vec3& change);
        void FollowParentPosition(glm::vec3 offset = glm::vec3(0));
        void FollowParentRotation();
        void FollowParentScale();
        template <typename T>
        void AddChild(T& entity);
        void AddChild(float id);

        // GETTERS
        unsigned GetID() const { return m_id; }
        unsigned GetParentID() const { return m_parentID; }
        std::vector<unsigned>& GetChildrenIDs() { return m_childrenIDs; }
        unsigned GetChildID(unsigned index) const { return m_childrenIDs[index]; }
        const std::string& GetName() const { return m_name; }

        bool HasParent();
        bool GetIsRotatable() { return m_isRotatable; }
        bool GetIsMovable() { return m_isMovable; }
        bool GetIsScalable() { return m_isScalable; }
        bool GetIsFollowingPosition() { return m_isFollowingPosition; }
        bool GetIsFollowingRotation() { return m_isFollowingRotation; }
        bool GetIsFollowingScale() { return m_isFollowingScale; }
        // bool HasAABB() { return m_hasAABB; }
        // bool HasOBB() { return m_hasOBB; }
        // bool GetIsColliding() const { return m_isColliding; }

        unsigned GetPlayerCompPos() const { return m_playerComponentPos; }
        unsigned GetAABBCompPos() const { return m_aabbComponentPos; }
        unsigned GetOBBCompPos() const { return m_obbComponentPos; }
        unsigned GetRigidBodyCompPos() const { return m_rigidBodyComponentPos; }
        unsigned GetCameraCompPos() const { return m_cameraComponentPos; }
        unsigned GetLightCompPos() const { return m_lightComponentPos; }

        Models::TexturedModel& GetModel() { return m_model; }
        const Models::TexturedModel& GetModel() const { return m_model; }
        glm::vec3& GetPosition() { return m_position; }
        glm::vec3& GetRotation() { return m_rotation; }
        glm::vec3& GetScale() { return m_scale; }
        const glm::vec3& GetPosition() const { return m_position; }
        const glm::vec3& GetRotation() const { return m_rotation; }
        const glm::vec3& GetScale() const { return m_scale; }

        // SETTERS
        void SetParentID(long id) { m_parentID = id; }
        void SetModel(Models::TexturedModel model) { m_model = model; }
        void SetPosition(glm::vec3 vec);
        void SetRotation(glm::vec3 vec);
        void SetPositionX(float value);
        void SetPositionY(float value);
        void SetPositionZ(float value);
        void SetRotationX(float value);
        void SetRotationY(float value);
        void SetRotationZ(float value);
        void SetScale(glm::vec3 vec) { m_scale = vec; }
        void SetIsRotatable(bool value) { m_isRotatable = value; }
        void SetIsMovable(bool value) { m_isMovable = value; }
        void SetIsScalable(bool value) { m_isScalable = value; }
        void SetIsFollowingPosition(bool value) { m_isFollowingPosition = value; }
        void SetIsFollowingRotation(bool value) { m_isFollowingRotation = value; }
        void SetIsFollowingScale(bool value) { m_isFollowingScale = value; }
        // void SetIsColliding(bool value) { m_isColliding = value; }

        void SetPlayerCompPos(unsigned value) { m_playerComponentPos = value; }
        void SetAABBCompPos(unsigned value) { m_aabbComponentPos = value; }
        void SetOBBCompPos(unsigned value) { m_obbComponentPos = value; }
        void SetRigidBodyCompPos(unsigned value) { m_rigidBodyComponentPos = value; }
        void SetCameraCompPos(unsigned value) { m_cameraComponentPos = value; }
        void SetLightCompPos(unsigned value) { m_lightComponentPos = value; }

    private:
        unsigned m_id;
        unsigned m_parentID;
        std::vector<unsigned> m_childrenIDs;
        std::string m_name;
        Models::TexturedModel m_model;
        glm::vec3 m_position, m_rotation, m_scale;

        bool m_isRotatable = true, m_isMovable = true, m_isScalable = true;
        bool m_isFollowingPosition = true, m_isFollowingRotation = true, m_isFollowingScale = true;
        // bool m_hasAABB, m_hasOBB;
        bool m_isColliding;

        unsigned m_playerComponentPos = -1;
        unsigned m_aabbComponentPos = -1;
        unsigned m_obbComponentPos = -1;
        unsigned m_rigidBodyComponentPos = -1;
        unsigned m_cameraComponentPos = -1;
        unsigned m_lightComponentPos = -1;
};
}
}

#endif
