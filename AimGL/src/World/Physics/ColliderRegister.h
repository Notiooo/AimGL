#pragma once

class Collider;

/**
 * \brief Manages the registration and tracking of colliders for collision detection.
 */
class ColliderRegister
{
public:
    /**
     * \brief Adds a collider to the registry for collision tracking.
     * \param collider Reference to the collider to be added.
     */
    void add(const Collider& collider);

    /**
     * \brief Removes a collider from the registry.
     * \param collider Reference to the collider to be removed.
     */
    void remove(const Collider& collider);

    /**
     * \brief Updates and checks for collisions among all registered colliders.
     */
    void updateAllCollisions();

    /**
     * \brief Identifies collisions with the specified collider.
     * \param collider The collider to check for collisions against.
     * \return List of colliders that are in collision with the given collider.
     */
    std::vector<const Collider*> findCollisions(const Collider& collider) const;

private:
    /**
     * \brief Adds colliders that are queued for addition to the collision system.
     */
    void addQueuedColliders();

    /**
     * \brief Removes colliders that are queued for removal from the collision system.
     */
    void removeCollidersQueuedToBeRemoved();

private:
    std::vector<const Collider*> mColliders;
    std::vector<const Collider*> mColliderToRemove;
    std::vector<const Collider*> mColliderToAdd;
};
