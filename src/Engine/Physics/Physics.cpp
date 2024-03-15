#include "Engine/Rendering/DisplayManager.hpp"
#include "Engine/Physics/Physics.hpp"
#include "Engine/Globals.hpp"
#include "Engine/Other/Math.hpp"
#include "Engine/Rendering/Loader.hpp"
#include "Engine/ECS/EntityManagement.hpp"
#include "Engine/ECS/ComponentManagement.hpp"
#include "Engine/Other/Printer.hpp"
#include "Engine/ECS/Components/RigidBodyComponent.hpp"
#include "Engine/Other/MouseRay.hpp"
#include <array>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <climits>
#include <limits>

using namespace MyEngine;

void Physics::CollisionSystem(const Entities::Camera& playerCamera) {
    AABBCollision();
    OBBCollision();
    RayCollision(playerCamera);
    // TODO AABB-OBB collision system
}

void Physics::CollisionResolution(CollisionInfo& collisionInfo) {
    Components::RigidBodyComponent& rb1 = *Components::GetRBFromEntity(collisionInfo.objectA->GetID());
    Components::RigidBodyComponent& rb2 = *Components::GetRBFromEntity(collisionInfo.objectB->GetID());

    float e = 1;
    float impulseForce = -(1 + e) * glm::dot(rb1.GetVelocity() - rb2.GetVelocity(), collisionInfo.normal) / ((1/rb1.GetMass() + (1/rb2.GetMass())));

    rb1.ApplyImpulse(collisionInfo.normal, impulseForce);
    rb2.ApplyImpulse(-collisionInfo.normal, impulseForce);
}

void Physics::OBBCollision() {
    for (auto& obb1 : Globals::obbComponentList) {
        int count = 0;
        for (auto& obb2 : Globals::obbComponentList) {
            if (obb1.GetEntityID() == obb2.GetEntityID()) { continue; }

            Physics::CollisionInfo collisionInfo;

            if (CheckCollisionOBB(collisionInfo, obb1, obb2)) {
                count++;

                const Components::RigidBodyComponent* iRB = Components::GetRBFromEntity(obb1.GetEntityID());
                if (iRB == nullptr) continue;
                const Components::RigidBodyComponent* jRB = Components::GetRBFromEntity(obb2.GetEntityID());
                if (jRB == nullptr) continue;

                CollisionResolution(collisionInfo);
            }
        }

        count ? obb1.SetIsColliding(true) : obb1.SetIsColliding(false);
    }
}

// SAT method
// https://gamedev.stackexchange.com/a/60225
// Gustavo Pezzi (pikuma) SAT col. detection
bool Physics::CheckCollisionOBB(CollisionInfo& collisionInfo, Components::OBBComponent& compA, Components::OBBComponent& compB) {
    std::array<glm::vec3, 8> vertsA = CreateVertList<Components::OBBComponent>(compA);
    std::array<glm::vec3, 8> vertsB = CreateVertList<Components::OBBComponent>(compB);

    OverlapInfo overlap1 = MaxOverlap(vertsA, vertsB);
    OverlapInfo overlap2 = MaxOverlap(vertsB, vertsA);

    if (overlap1.overlap >= 0 && overlap2.overlap >= 0) {
        collisionInfo.objectA = Globals::GetEntity(compA.GetEntityID());
        collisionInfo.objectB = Globals::GetEntity(compB.GetEntityID());

        if (overlap1.overlap > overlap2.overlap) {
            collisionInfo.overlap = overlap1.overlap;
            collisionInfo.normal = overlap1.normal;
        } else {
            collisionInfo.overlap = overlap2.overlap;
            collisionInfo.normal = overlap2.normal;
        }

        return true;
    }

    return false;
}

Physics::OverlapInfo Physics::MaxOverlap(const std::array<glm::vec3, 8>& vertsA, const std::array<glm::vec3, 8>& vertsB) {
    float overlap = std::numeric_limits<float>::max();
    glm::vec3 overlapNormal;

    std::array<glm::vec3, 6> normalsA = CreateNormalsList(vertsA);

    for (glm::vec3 normal : normalsA) {
        float aMin = std::numeric_limits<float>::max();
        float bMin = std::numeric_limits<float>::max();
        float aMax = std::numeric_limits<float>::min();
        float bMax = std::numeric_limits<float>::min();

        SATProjection(normal, vertsA, aMin, aMax);
        SATProjection(normal, vertsB, bMin, bMax);

        float currentOverlap = std::numeric_limits<float>::lowest();
        currentOverlap = std::min(aMax- bMin, bMax - aMin); // negative means there's not overlap on that axis

        if (currentOverlap < overlap) {
            overlap = currentOverlap;
            overlapNormal = normal;
        }
    }

    return { overlap, overlapNormal };
}

void Physics::SATProjection(const glm::vec3& axis, const std::array<glm::vec3, 8>& corners, float& min, float& max) {
    for (auto& c : corners) {
        float dot = glm::dot(c, axis);
        if (dot < min) min = dot;
        if (dot > max) max = dot;
    }
}

bool Physics::IsBetween(float value, float lower, float upper) {
    return (lower <= value) && (upper >= value);
}

void Physics::AABBCollision() {
    for (auto& aabb : Globals::aabbComponentList) {
        aabb.RecalculateAABB();
    }

    for (auto& aabb1 : Globals::aabbComponentList) {
        int count = 0;
        for (auto& aabb2 : Globals::aabbComponentList)
        {
            if (aabb1.GetEntityID() == aabb2.GetEntityID()) { continue; }

            if (CheckCollisionAABB(&aabb1, &aabb2))
            {
                count++;

                const Components::RigidBodyComponent* rb1 = Components::GetRBFromEntity(aabb1.GetEntityID());
                if (rb1 == nullptr) continue;
                const Components::RigidBodyComponent* rb2 = Components::GetRBFromEntity(aabb2.GetEntityID());
                if (rb2 == nullptr) continue;

                // CollisionResolution<Components::AABBComponent>(aabb1, aabb2);
            }
        }

        count ? aabb1.SetIsColliding(true) : aabb1.SetIsColliding(false);
    }
}

bool Physics::CheckCollisionAABB(Components::AABBComponent* a, Components::AABBComponent* b) {
    Entities::Entity* entityA = Globals::GetEntity(a->GetEntityID());
    Entities::Entity* entityB = Globals::GetEntity(b->GetEntityID());

    glm::vec3 sizeA = a->GetModel().GetRawModel().GetBoundingSizes() * entityA->GetScale();
    glm::vec3 sizeB = b->GetModel().GetRawModel().GetBoundingSizes() * entityB->GetScale();

    // credit: Studio Freya
    bool x = (std::abs(entityA->GetPosition().x - entityB->GetPosition().x)) <= (sizeA.x/2 + sizeB.x/2);
    bool y = (std::abs(entityA->GetPosition().y - entityB->GetPosition().y)) <= (sizeA.y/2 + sizeB.y/2);
    bool z = (std::abs(entityA->GetPosition().z - entityB->GetPosition().z)) <= (sizeA.z/2 + sizeB.z/2);

    if (x && y && z) { return 1; }
    return 0;
}
void Physics::RayCollision(const Entities::Camera& playerCamera) {
    for (auto& ray : Globals::rayComponentList) {
        if (ray.GetEntityID() == Globals::playerComponentList.at(0).GetEntityID() && !playerCamera.GetMouseLocked()) { continue; }

        for (auto& obb : Globals::obbComponentList) {
            if (ray.GetEntityID() == obb.GetEntityID()) { continue; }

            bool test = CheckRayCollision<Components::OBBComponent>(&ray, &obb, playerCamera);
            if (test) {
                obb.SetIsColliding(true);
                ray.SetCollidingID(obb.GetEntityID());
                break;
            }

            ray.SetCollidingID(-1);

            // disabled for AABBs
            // for (auto& aabb : Globals::aabbComponentList) {
            //     if (ray.GetEntityID() == aabb.GetEntityID()) { continue; }
            //
            //     bool test = RayCollision<Components::AABBComponent>(&ray, &aabb, playerCamera);
            //     if (test) {
            //         aabb.SetIsColliding(true);
            //         ray.SetCollidingID(aabb.GetEntityID());
            //         break;
            //     }
            //
            //     ray.SetCollidingID(-1);
            // }
        }
    }
}

// The slab method
// Only tuned for OBBs, imprecise for AABBs
// TODO There's a better optimized way: https://tavianator.com/2022/ray_box_boundary.html
template <class T>
bool Physics::CheckRayCollision(Components::RayComponent* ray, T* box, const Entities::Camera& playerCamera) {
    const Entities::Entity& raysEntity = Globals::entityMap.at(ray->GetEntityID());
    const Entities::Entity& boxEntity = Globals::entityMap.at(box->GetEntityID());
    auto extremes = boxEntity.GetModel().GetRawModel().GetExtremes();

    // TODO please change the format of the extremes container (in the obj loader)
    glm::vec3 maxVec(extremes[0][0], extremes[1][0], extremes[2][0]); // top right corner
    glm::vec3 minVec(extremes[0][1], extremes[1][1], extremes[2][1]); //  bottom left corner
    glm::mat4 mat = Other::Maths::CreateTransformMatrix(boxEntity.GetPosition(), boxEntity.GetRotation(), boxEntity.GetScale());
    maxVec = mat * glm::make_vec4(maxVec);
    minVec = mat * glm::make_vec4(minVec);

    glm::vec3 origin;
    if (ray->GetEntityID() == Globals::playerComponentList.at(0).GetEntityID()) { origin = glm::vec3(playerCamera.GetPosition()); }
    else { origin = raysEntity.GetPosition(); }

    glm::vec3 inv;
    inv.x = 1 / ray->GetRay().x;
    inv.y = 1 / ray->GetRay().y;
    inv.z = 1 / ray->GetRay().z;
    inv = glm::normalize(inv);

    float tmin = std::numeric_limits<float>::lowest();
    float tmax = std::numeric_limits<float>::max();

    float tx1 = (minVec.x - origin.x) * inv.x;
    float tx2 = (maxVec.x - origin.x) * inv.x;
    tmin = std::max(std::min(tx1, tx2), tmin);
    tmax = std::min(std::max(tx1, tx2), tmax);
    float ty1 = (minVec.y - origin.y) * inv.y;
    float ty2 = (maxVec.y - origin.y) * inv.y;
    tmin = std::max(std::min(ty1, ty2), tmin);
    tmax = std::min(std::max(ty1, ty2), tmax);
    float tz1 = (minVec.z - origin.z) * inv.z;
    float tz2 = (maxVec.z - origin.z) * inv.z;
    tmin = std::max(std::min(tz1, tz2), tmin);
    tmax = std::min(std::max(tz1, tz2), tmax);

    return tmin <= tmax;
}

// TODO: optimize
template <class T>
std::array<glm::vec3, 8> Physics::CreateVertList(T& box) {
    const Entities::Entity& entity = Globals::entityMap.at(box.GetEntityID());
    auto& extremes = entity.GetModel().GetRawModel().GetExtremes();

    std::array<glm::vec3, 8> corners;
    corners[0] = glm::vec3(extremes[0][0], extremes[1][0], extremes[2][0]); // xmax, ymax, zmax.  a
    corners[7] = glm::vec3(extremes[0][1], extremes[1][1], extremes[2][1]); // xmin, ymin, zmin.  h
    corners[1] = glm::vec3(extremes[0][0], extremes[1][0], extremes[2][1]); // xmax, ymax, zmin.  b
    corners[2] = glm::vec3(extremes[0][0], extremes[1][1], extremes[2][0]); // xmax, ymin, zmax.  c
    corners[3] = glm::vec3(extremes[0][0], extremes[1][1], extremes[2][1]); // xmax, ymin, zmin.  d
    corners[4] = glm::vec3(extremes[0][1], extremes[1][0], extremes[2][0]); // xmin, ymax, zmax.  e
    corners[6] = glm::vec3(extremes[0][1], extremes[1][1], extremes[2][0]); // xmin, ymin, zmax.  g
    corners[5] = glm::vec3(extremes[0][1], extremes[1][0], extremes[2][1]); // xmin, ymax, zmin.  f

    glm::mat4 mat = Other::Maths::CreateTransformMatrix(entity.GetPosition(), entity.GetRotation(), entity.GetScale());
    for (glm::vec3& c : corners)
        c = mat * glm::make_vec4(c);

    return corners;
}

std::array<glm::vec3, 6> Physics::CreateNormalsList(const std::array<glm::vec3, 8>& corners) {
    std::array<glm::vec3, 6> normals;
    glm::vec3 ab(corners[1] - corners[0]);
    glm::vec3 ac(corners[2] - corners[0]);
    normals[0] = glm::cross(ab, ac);

    glm::vec3 bf(corners[5] - corners[1]);
    glm::vec3 bd(corners[3] - corners[1]);
    normals[1] = glm::cross(bf, bd);

    glm::vec3 fe(corners[4] - corners[5]);
    glm::vec3 fh(corners[7] - corners[5]);
    normals[2] = glm::cross(fe, fh);

    glm::vec3 ea(corners[0] - corners[4]);
    glm::vec3 eg(corners[6] - corners[4]);
    normals[3] = glm::cross(ea, eg);

    normals[4] = glm::cross(ab, ea);

    glm::vec3 cd(corners[3] - corners[1]);
    glm::vec3 cg(corners[6] - corners[1]);
    normals[5] = -glm::cross(cd, cg);

    return normals;
}
