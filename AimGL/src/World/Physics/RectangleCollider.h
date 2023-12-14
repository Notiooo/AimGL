#pragma once
#include "Collider.h"

/**
 * \brief Represents a rectangle-shaped collider for collision detection.
 */
class RectangleCollider : public Collider
{
public:
    /**
     * \brief Constructs a RectangleCollider object.
     * \param colliderRegister Reference to the collision register for tracking this collider.
     * \param min The minimum corner point of the rectangle in 3D space.
     * \param max The maximum corner point of the rectangle in 3D space.
     */
    RectangleCollider(ColliderRegister& colliderRegister, const glm::vec3& min,
                      const glm::vec3& max);

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

    glm::vec3 min;
    glm::vec3 max;
};
