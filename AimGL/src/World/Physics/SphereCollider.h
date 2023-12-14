#pragma once
#include "Collider.h"

/**
 * \brief Represents a sphere-shaped collider for collision detection.
 */
class SphereCollider : public Collider
{
public:
    /**
     * \brief Constructs a SphereCollider object.
     * \param colliderRegister Reference to the collision register for tracking this collider.
     * \param center The center point of the sphere in 3D space.
     * \param radius The radius of the sphere.
     */
    SphereCollider(ColliderRegister& colliderRegister, const glm::vec3& center, float radius);

    /**
     * \brief Checks for collision with another collider.
     * \param other The collider to check collision against.
     * \return True if there is a collision, false otherwise.
     */
    [[nodiscard]] bool checkCollision(const Collider& other) const override;

    /**
     * \brief Checks for collision with a SphereCollider.
     * \param other The SphereCollider to check collision against.
     * \return True if there is a collision, false otherwise.
     */
    [[nodiscard]] bool checkCollisionWith(const SphereCollider& other) const override;

    /**
     * \brief Checks for collision with another RectangleCollider.
     * \param other The RectangleCollider to check collision against.
     * \return True if there is a collision, false otherwise.
     */
    [[nodiscard]] bool checkCollisionWith(const RectangleCollider& other) const override;

    /**
     * \brief Checks for collision with a RayCollider.
     * \param other The RayCollider to check collision against.
     * \return True if there is a collision, false otherwise.
     */
    [[nodiscard]] bool checkCollisionWith(const RayCollider& other) const override;

    glm::vec3 center;
    float radius;
};
