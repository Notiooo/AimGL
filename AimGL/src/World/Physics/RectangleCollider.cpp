#include "RectangleCollider.h"

#include "World/Physics/Collisions.h"
#include "pch.h"

RectangleCollider::RectangleCollider(ColliderRegister& colliderRegister, const glm::vec3& min,
                                     const glm::vec3& max)
    : Collider(colliderRegister)
    , min(min)
    , max(max)
{
}

bool RectangleCollider::checkCollision(const Collider& other) const
{
    return other.checkCollisionWith(*this);
}

bool RectangleCollider::checkCollisionWith(const SphereCollider& other) const
{
    return checkSphereRectangleCollision(other, *this);
}

bool RectangleCollider::checkCollisionWith(const RectangleCollider& other) const
{
    return (min.x <= other.max.x && max.x >= other.min.x) &&
           (min.y <= other.max.y && max.y >= other.min.y) &&
           (min.z <= other.max.z && max.z >= other.min.z);
}

bool RectangleCollider::checkCollisionWith(const RayCollider& other) const
{
    return checkRayRectangleCollision(other, *this);
}
