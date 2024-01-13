#include "TargetManager.h"
#include "World/Physics/ColliderRegister.h"
#include "pch.h"

TargetManager::TargetManager(ColliderRegister& colliderRegister, const glm::vec3& position,
                             const sf::Time& timeToSpawn, const sf::Time& timeToDisappear)
    : mColliderRegister(colliderRegister)
    , mPosition(position)
    , mTimeToSpawn(timeToSpawn)
    , mTimeToDisappear(timeToDisappear)
    , mSpherePrefab("resources/Models/sphere.obj")
{
    mBuffer.loadFromFile("resources/Sounds/target-shot.wav");
    mSound.setBuffer(mBuffer);
    mSpherePrefab.setScale(0.3);
}

void TargetManager::draw(const Renderer& rendererTarget, const Camera& camera) const
{
    for (const auto& targetWithSpawntime: mTargetsWithSpawntime)
    {
        targetWithSpawntime.target.draw(rendererTarget, camera);
    }
}

void TargetManager::removeShotTargets()
{
    std::erase_if(mTargetsWithSpawntime,
                  [this](const auto& targetWithSpawnTime)
                  {
                      if (targetWithSpawnTime.target.hasBeenShot())
                      {
                          this->mSound.play();
                          return true;
                      }
                      return false;
                  });
}

bool TargetManager::shouldNewTargetBeSpawn() const
{
    return mNextSpawnClock.getElapsedTime() > mTimeToSpawn;
}

bool TargetManager::shouldOldTargetBeRemoved() const
{
    return (not mTargetsWithSpawntime.empty() and
            mTargetsWithSpawntime.front().timeSinceSpawn.getElapsedTime() > mTimeToDisappear);
}

void TargetManager::spawnNewTarget()
{
    auto targetWithSpawntime = SpawnedTarget(
        {mColliderRegister, mPosition + generateNewRandomOffset(), mSpherePrefab}, {});
    mTargetsWithSpawntime.emplace_back(std::move(targetWithSpawntime));
    auto& targetWithSpawnTime = mTargetsWithSpawntime.back();
    targetWithSpawnTime.target.setMovement(mTargetsDirection, mTargetsSpeed);
    targetWithSpawnTime.timeSinceSpawn.restart();
    mNextSpawnClock.restart();
}

void TargetManager::removeOldTarget()
{
    mTargetsWithSpawntime.pop_front();
}

void TargetManager::update(const float& deltaTime)
{
    for (auto& targetWithSpawnTime: mTargetsWithSpawntime)
    {
        targetWithSpawnTime.target.update(deltaTime);
    }
    removeShotTargets();
    if (mIsManagerActive)
    {
        if (shouldNewTargetBeSpawn())
        {
            spawnNewTarget();
        }
        if (shouldOldTargetBeRemoved())
        {
            removeOldTarget();
        }
    }
}

void TargetManager::start()
{
    mNextSpawnClock.restart();
    mIsManagerActive = true;
}

void TargetManager::stop()
{
    mIsManagerActive = false;
}

void TargetManager::setPosition(const glm::vec3& newPosition)
{
    mPosition = newPosition;
}

void TargetManager::setSpawnRange(const glm::vec3& minPadding, const glm::vec3& maxPadding)
{
    mMinPadding = minPadding;
    mMaxPadding = maxPadding;
}

void TargetManager::setTargetMovement(const glm::vec3& direction, float speed)
{
    mTargetsDirection = direction;
    mTargetsSpeed = speed;
}

glm::vec3 TargetManager::generateNewRandomOffset() const
{
    static std::random_device rd;
    static std::mt19937 e{rd()};
    std::uniform_real_distribution distX{mMinPadding.x, mMaxPadding.x};
    std::uniform_real_distribution distY{mMinPadding.y, mMaxPadding.y};
    std::uniform_real_distribution distZ{mMinPadding.z, mMaxPadding.z};
    return {distX(e), distY(e), distZ(e)};
}
