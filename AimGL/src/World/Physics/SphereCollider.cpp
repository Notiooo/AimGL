#include "SphereCollider.h"

#include "World/Physics/Collisions.h"
#include "pch.h"

SphereCollider::SphereCollider(ColliderRegister& colliderRegister, const glm::vec3& center,
                               float radius)
    : Collider(colliderRegister)
    , center(center)
    , radius(radius)
{
}

bool SphereCollider::checkCollision(const Collider& other) const
{
    return other.checkCollisionWith(*this);
}

bool SphereCollider::checkCollisionWith(const SphereCollider& other) const
{
    float distanceSquared = glm::distance(center, other.center);
    float radiusSum = radius + other.radius;
    return distanceSquared < (radiusSum * radiusSum);
}

bool SphereCollider::checkCollisionWith(const RectangleCollider& other) const
{
    return checkSphereRectangleCollision(*this, other);
}

bool SphereCollider::checkCollisionWith(const RayCollider& other) const
{
    return checkRaySphereCollision(other, *this);
}
