#pragma once
#include "Collider.h"

/**
 * \brief A ray that allows to check collisions between other types of colliders
 */
class RayCollider : public Collider
{
public:
    /**
     * \brief Constructs a Ray object.
     * \param colliderRegister Reference to the collision register for tracking this collider.
     * \param origin The starting point of the ray in 3D space.
     * \param direction The direction vector of the ray. This vector should be normalized.
     * \param length (Optional) The length of the ray. Default is 100 units.
     */
    RayCollider(ColliderRegister& colliderRegister, const glm::vec3& origin,
                const glm::vec3& direction, float length = 100);

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
     * \brief Checks for collision with a RectangleCollider.
     * \param other The RectangleCollider to check collision against.
     * \return True if there is a collision, false otherwise.
     */
    [[nodiscard]] bool checkCollisionWith(const RectangleCollider& other) const override;

    /**
     * \brief Checks for collision with another RayCollider.
     * \param other The RayCollider to check collision against.
     * \return True if there is a collision, false otherwise.
     */
    [[nodiscard]] bool checkCollisionWith(const RayCollider& other) const override;

    glm::vec3 origin;
    glm::vec3 direction;
    float length;
};
