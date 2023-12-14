#pragma once
#include "World/Physics/Collider.h"
#include "World/Physics/ColliderTag.h"


/**
 * \brief A template class for colliders that are both drawable and functional in collision
 * detection. \tparam ColliderType The type of collider this class is templating (e.g.,
 * SphereCollider, RectangleCollider).
 */
template<typename ColliderType>
class DrawableCollider
{
public:
    virtual ~DrawableCollider() = default;

    /**
     * \brief Constructor that initializes the collider with provided parameters.
     * \tparam Args The types of arguments to forward to the ColliderType's constructor.
     * \param params Arguments to forward to the ColliderType's constructor.
     */
    template<typename... Args>
    explicit DrawableCollider(Args&&... params);

    /**
     * \brief Sets a callback function to be executed when a collision occurs.
     * \param callbackFunction The function to be called upon collision detection.
     */
    void callback(std::function<void(const Collider&)> callbackFunction);

    /**
     * \brief Retrieves the tag of the collider.
     * \return The tag that identifies the type of the collider.
     */
    [[nodiscard]] ColliderTag colliderTag() const;

    /**
     * \brief Sets the tag identifying the type of the collider.
     * \param colliderTag The tag to assign to the collider.
     */
    void colliderTag(ColliderTag colliderTag);

protected:
    ColliderType mCollider;
};

template<typename ColliderType>
template<typename... Args>
DrawableCollider<ColliderType>::DrawableCollider(Args&&... params)
    : mCollider(std::forward<Args>(params)...)
{
}

template<typename ColliderType>
void DrawableCollider<ColliderType>::callback(std::function<void(const Collider&)> callbackFunction)
{
    mCollider.callback(callbackFunction);
}

template<typename ColliderType>
ColliderTag DrawableCollider<ColliderType>::colliderTag() const
{
    return mCollider.colliderTag();
}

template<typename ColliderType>
void DrawableCollider<ColliderType>::colliderTag(ColliderTag colliderTag)
{
    mCollider.colliderTag(colliderTag);
}
