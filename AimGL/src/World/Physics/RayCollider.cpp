#include "RayCollider.h"
#include "World/Physics/Collisions.h"
#include "pch.h"

RayCollider::RayCollider(ColliderRegister& colliderRegister, const glm::vec3& origin,
                         const glm::vec3& direction, float length)
    : Collider(colliderRegister)
    , origin(origin)
    , direction(glm::normalize(direction))
    , length(length)
{
}

bool RayCollider::checkCollision(const Collider& other) const
{
    return other.checkCollisionWith(*this);
}

bool RayCollider::checkCollisionWith(const SphereCollider& other) const
{
    return checkRaySphereCollision(*this, other);
}

bool RayCollider::checkCollisionWith(const RectangleCollider& other) const
{
    return checkRayRectangleCollision(*this, other);
}

bool RayCollider::checkCollisionWith(const RayCollider& other) const
{
    // TODO: (anyway I guess I won't need this :D)
    return false;
}
