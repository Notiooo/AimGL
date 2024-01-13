#include "Target.h"
#include "World/Physics/ColliderRegister.h"
#include "pch.h"


Target::Target(ColliderRegister& colliderRegister, const glm::vec3& position)
    : mSphere("resources/Models/sphere.obj")
    , mAABB(colliderRegister, {0, 0, 0}, mSphere.dimensions())
    , mPosition(position)
{
    prepareTarget(position);
}

Target::Target(ColliderRegister& colliderRegister, const glm::vec3& position, Model model)
    : mSphere(std::move(model))
    , mAABB(colliderRegister, {0, 0, 0}, mSphere.dimensions())
    , mPosition(position)
{
    prepareTarget(position);
}

Target::Target(const Target& rhs)
    : mAABB(rhs.mAABB)
    , mSphere(rhs.mSphere)
    , mPosition(rhs.mPosition)
    , mHasBeenShot(rhs.mHasBeenShot)
    , mSpeed(rhs.mSpeed)
    , mDirectionMovement(rhs.mDirectionMovement)
{
    prepareTarget(mPosition);
}

void Target::prepareTarget(const glm::vec3& position)
{
    mAABB.colliderTag(ColliderTag::Solid);
    mAABB.callback(
        [this](const Collider& collider)
        {
            if (collider.colliderTag() == ColliderTag::GunShot and not mHasBeenShot)
            {
                mHasBeenShot = true;
            }
        });
    mSphere.setPosition(position);
}

void Target::draw(const Renderer& target, const Camera& camera) const
{
    if (not mHasBeenShot)
    {
        mSphere.draw(target, camera);
        mAABB.draw(target, camera);
    }
}

void Target::update(const float& deltaTime)
{
    if (not mHasBeenShot)
    {
        const auto deltaPosition = mDirectionMovement * mSpeed * deltaTime;
        mSphere.setPosition(mSphere.position() + deltaPosition, Model::Origin::Center);
        mAABB.setPosition(mSphere.position() - mSphere.dimensions() / 2.f);
    }
}

bool Target::hasBeenShot() const
{
    return mHasBeenShot;
}

void Target::setMovement(const glm::vec3& direction, float speed)
{
    mDirectionMovement = direction;
    mSpeed = speed;
}
