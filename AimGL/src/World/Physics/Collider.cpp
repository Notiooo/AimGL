#include "Collider.h"

#include "World/Physics/ColliderRegister.h"
#include "pch.h"
#include <utility>

Collider::Collider(ColliderRegister& colliderRegister)
    : mColliderRegister(colliderRegister)
{
    mColliderRegister.add(*this);
}

Collider::~Collider()
{
    mColliderRegister.remove(*this);
}

void Collider::executeCallback(const Collider& other) const
{
    if (mCallback)
    {
        mCallback(other);
    }
}

void Collider::callback(std::function<void(const Collider&)> callbackFunction)
{
    mCallback = std::move(callbackFunction);
}

ColliderTag Collider::colliderTag() const
{
    return mColliderTag;
}

void Collider::colliderTag(ColliderTag colliderTag)
{
    mColliderTag = colliderTag;
}
