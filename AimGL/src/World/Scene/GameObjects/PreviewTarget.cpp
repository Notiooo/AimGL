#include "PreviewTarget.h"
#include "World/Physics/ColliderRegister.h"
#include "pch.h"

PreviewTarget::PreviewTarget(ColliderRegister& colliderRegister, const glm::vec3& position)
    : mAABB(colliderRegister, {0, 0, 0}, {0.5, 0.5, 0.5})
    , mSphere("resources/Models/sphere.obj")
    , mPosition(position)
{
    mBuffer.loadFromFile("resources/Sounds/target-shot.wav");
    mSound.setBuffer(mBuffer);
    mAABB.callback(
        [this](const Collider& collider)
        {
            if (collider.colliderTag() == ColliderTag::GunShot && not mIsAboutToBeDeleted)
            {
                mSound.play();
                mIsAboutToBeDeleted = true;
            }
        });
    mSphere.setScale(0.5);
    mSphere.setPosition(position);
}

void PreviewTarget::draw(const Renderer& target, const Camera& camera) const
{
    if (not mIsAboutToBeDeleted)
    {
        mSphere.draw(target, camera);
        mAABB.draw(target, camera);
    }
}

void PreviewTarget::update(const float& deltaTime)
{
    if (not mIsAboutToBeDeleted)
    {
        mAABB.setPosition(mSphere.position() - mSphere.dimensions() / 2.f);
    }
}
