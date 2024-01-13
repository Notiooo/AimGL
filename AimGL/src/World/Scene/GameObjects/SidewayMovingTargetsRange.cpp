#include "SidewayMovingTargetsRange.h"
#include "pch.h"

SidewayMovingTargetsRange::SidewayMovingTargetsRange(ColliderRegister& colliderRegister,
                                                     const glm::vec3& position)
    : mButtonStand(colliderRegister, position)
    , mPosition(position)
    , mSmallerCrate(colliderRegister, position)
    , mMediumCrate(colliderRegister, position)
    , mLargeCrate(colliderRegister, position)
    , mDirectionArrowTexture("resources/Textures/arrow-up.png")
    , mDirectionArrowPointingButton(mDirectionArrowTexture)
    , mTrainingLogoTexture("resources/Textures/moving-targets.png")
    , mTrainingLogo(mTrainingLogoTexture)
    , mTargetManager(colliderRegister, {0, 0, 0}, sf::seconds(1.5), sf::seconds(5))
{
    mLargeCrate.setScale(1.5);
    mMediumCrate.setScale(1);
    mSmallerCrate.setScale(0.5);
    setPosition(mPosition);
    mSmallerCrate.setRotation({0, 90, 0});
    mMediumCrate.setRotation({0, 90, 0});
    mLargeCrate.setRotation({0, 90, 0});
    mDirectionArrowPointingButton.setRotation({0, 0, 180});
    mDirectionArrowPointingButton.setScale(0.2);
    mTrainingLogo.setRotation({180, 0, 0});
    mTrainingLogo.setScale(3.f);
    mTargetManager.setTargetMovement({1, 0, 0}, 4);
    mTargetManager.setSpawnRange({0, 0, 0}, {0, 4, 4});
    mButtonStand.onClick(
        [this]()
        {
            toggleShootingRange();
        });
}

void SidewayMovingTargetsRange::draw(const Renderer& target, const Camera& camera) const
{
    mButtonStand.draw(target, camera);
    mLargeCrate.draw(target, camera);
    mMediumCrate.draw(target, camera);
    mSmallerCrate.draw(target, camera);
    mDirectionArrowPointingButton.draw(target, camera);
    mTargetManager.draw(target, camera);
    mTrainingLogo.draw(target, camera);
}

void SidewayMovingTargetsRange::update(const float& deltaTime)
{
    mButtonStand.update(deltaTime);
    mTargetManager.update(deltaTime);
}

void SidewayMovingTargetsRange::handleEvent(const sf::Event& event)
{
    mButtonStand.handleEvent(event);
}

void SidewayMovingTargetsRange::showDebugImGui(std::string name)
{
    name = "[Model] " + name;
    ImGui::Begin(name.c_str());
    ImGui::SliderFloat3("Position", &mPosition[0], -50, 50.f);
    ImGui::End();
    setPosition(mPosition);
}

void SidewayMovingTargetsRange::setPosition(const glm::vec3& newPosition)
{
    mTargetManager.setPosition(newPosition + glm::vec3{0, 0, BOXES_DISTANCE + 2.f});
    mButtonStand.setPosition(newPosition + glm::vec3{2.5, 0, 0});
    mLargeCrate.setPosition(newPosition + glm::vec3{0, 0.75, BOXES_DISTANCE});
    mMediumCrate.setPosition(newPosition + glm::vec3{2.5, 0.5, BOXES_DISTANCE});
    mSmallerCrate.setPosition(newPosition + glm::vec3{4.5, 0.25, BOXES_DISTANCE});
    mDirectionArrowPointingButton.setPosition(newPosition + glm::vec3{2.3, 0.3, 0});
    mTrainingLogo.setPosition(newPosition + glm::vec3{2, 5, BOXES_DISTANCE});
}

void SidewayMovingTargetsRange::toggleShootingRange()
{
    if (mIsShootingRangeActive)
    {
        mTargetManager.stop();
        mIsShootingRangeActive = false;
    }
    else
    {
        mTargetManager.start();
        mIsShootingRangeActive = true;
    }
}
