#include "ColliderRegister.h"
#include "Collider.h"
#include "pch.h"

void ColliderRegister::add(const Collider& collider)
{
    mColliderToAdd.push_back(&collider);
}

void ColliderRegister::remove(const Collider& collider)
{
    mColliderToRemove.push_back(&collider);
}

void ColliderRegister::addQueuedColliders()
{
    for (auto& collider: mColliderToAdd)
    {
        mColliders.push_back(collider);
    }
    mColliderToAdd.clear();
}

void ColliderRegister::removeCollidersQueuedToBeRemoved()
{
    for (auto& collider: mColliderToRemove)
    {
        auto it = std::find(mColliders.begin(), mColliders.end(), collider);
        if (it != mColliders.end())
        {
            mColliders.erase(it);
        }
    }
    mColliderToRemove.clear();
}

void ColliderRegister::updateAllCollisions()
{
    addQueuedColliders();
    removeCollidersQueuedToBeRemoved();
    for (size_t i = 0; i < mColliders.size(); ++i)
    {
        for (size_t j = i + 1; j < mColliders.size(); ++j)
        {
            if (mColliders[i]->checkCollision(*mColliders[j]))
            {
                mColliders[i]->executeCallback(*mColliders[j]);
                mColliders[j]->executeCallback(*mColliders[i]);
            }
        }
    }
}
