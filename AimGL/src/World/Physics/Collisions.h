#pragma once


class SphereCollider;
class RectangleCollider;
class RayCollider;

/**
 * \brief Checks for collision between a sphere and a rectangle.
 * \param sphere The SphereCollider to check for collision.
 * \param rectangle The RectangleCollider to check against.
 * \return True if there is a collision between the sphere and rectangle, false otherwise.
 */
bool checkSphereRectangleCollision(const SphereCollider& sphere,
                                   const RectangleCollider& rectangle);

/**
 * \brief Checks for collision between a ray and a rectangle.
 * \param ray The RayCollider to check for collision.
 * \param rectangle The RectangleCollider to check against.
 * \return True if the ray collides with the rectangle, false otherwise.
 */
bool checkRayRectangleCollision(const RayCollider& ray, const RectangleCollider& rectangle);

/**
 * \brief Checks for collision between a ray and a sphere.
 * \param ray The RayCollider to check for collision.
 * \param sphere The SphereCollider to check against.
 * \return True if the ray collides with the sphere, false otherwise.
 */
bool checkRaySphereCollision(const RayCollider& ray, const SphereCollider& sphere);
