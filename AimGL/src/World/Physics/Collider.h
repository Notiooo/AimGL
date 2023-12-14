#pragma once
#include "World/Physics/ColliderTag.h"

class SphereCollider;
class RectangleCollider;
class RayCollider;
class ColliderRegister;

/**
 * \brief Base class for collision detection objects.
 */
class Collider
{
public:
    /**
     * \brief Constructor that registers the collider with a collision management system.
     * \param colliderRegister Reference to the collision register for tracking colliders.
     */
    explicit Collider(ColliderRegister& colliderRegister);
    virtual ~Collider();

    /**
     * \brief Pure virtual method to check collision with another collider.
     * \param other Reference to another collider.
     * \return True if collision occurs, false otherwise.
     */
    [[nodiscard]] virtual bool checkCollision(const Collider& other) const = 0;

    /**
     * \brief Checks collision with a SphereCollider.
     * \param other SphereCollider to check against.
     * \return True if collision occurs, false otherwise.
     */
    [[nodiscard]] virtual bool checkCollisionWith(const SphereCollider& other) const = 0;

    /**
     * \brief Checks collision with a RectangleCollider.
     * \param other RectangleCollider to check against.
     * \return True if collision occurs, false otherwise.
     */
    [[nodiscard]] virtual bool checkCollisionWith(const RectangleCollider& other) const = 0;

    /**
     * \brief Checks collision with a RayCollider.
     * \param other RayCollider to check against.
     * \return True if collision occurs, false otherwise.
     */
    [[nodiscard]] virtual bool checkCollisionWith(const RayCollider& other) const = 0;

    /**
     * \brief Executes a callback function upon collision detection.
     * \param other Collider that triggered the callback.
     */
    void executeCallback(const Collider& other) const;

    /**
     * \brief Sets the callback function to be executed on collision.
     * \param callbackFunction The function to call on collision.
     */
    virtual void callback(std::function<void(const Collider&)> callbackFunction);

    /**
     * \brief Gets the tag identifying the type of collider.
     * \return The collider's tag.
     */
    [[nodiscard]] ColliderTag colliderTag() const;

    /**
     * \brief Sets the tag identifying the type of collider.
     * \param colliderTag The tag to set.
     */
    void colliderTag(ColliderTag colliderTag);

private:
    std::function<void(const Collider&)> mCallback;
    ColliderRegister& mColliderRegister;
    ColliderTag mColliderTag{ColliderTag::None};
};