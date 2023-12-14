#include "Collisions.h"
#include "pch.h"

#include "World/Physics/RayCollider.h"
#include "World/Physics/RectangleCollider.h"
#include "World/Physics/SphereCollider.h"

bool checkSphereRectangleCollision(const SphereCollider& sphere, const RectangleCollider& rectangle)
{
    glm::vec3 closestPoint = glm::clamp(sphere.center, rectangle.min, rectangle.max);
    float distanceSquared = glm::distance(sphere.center, closestPoint);
    return distanceSquared < (sphere.radius * sphere.radius);
}

bool checkRaySphereCollision(const RayCollider& ray, const SphereCollider& sphere)
{
    // TODO: This Ray-Sphere Collision
    return false;
}

bool checkRayRectangleCollision(const RayCollider& ray, const RectangleCollider& rectangle)
{
    float tMin = 0.0f;
    float tMax = ray.length;

    for (int i = 0; i < 3; ++i)
    {
        if (std::abs(ray.direction[i]) < std::numeric_limits<float>::epsilon())
        {
            if (ray.origin[i] < rectangle.min[i] || ray.origin[i] > rectangle.max[i])
            {
                return false;
            }
        }
        else
        {
            float ood = 1.0f / ray.direction[i];
            float t1 = (rectangle.min[i] - ray.origin[i]) * ood;
            float t2 = (rectangle.max[i] - ray.origin[i]) * ood;
            if (t1 > t2)
            {
                std::swap(t1, t2);
            }
            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);
            if (tMin > tMax)
            {
                return false;
            }
        }
    }
    return tMin <= ray.length;
}
