#include "ShootingRange.h"
#include "pch.h"

ShootingRange::ShootingRange(ColliderRegister& colliderRegister, const glm::vec3& position)
    : mButtonStand(colliderRegister, position)
    , mShootingRange("resources/Models/shooting-board/shooting-board.obj",
                     {{"resources/Models/shooting-board/diffuse.png", Texture::Type::Diffuse},
                      {"resources/Models/shooting-board/specular.png", Texture::Type::Specular}})
    , mPosition(position)
    , mAABB(colliderRegister, {0, 0, 0}, mShootingRange.dimensions())
    , mSmallerCrate(colliderRegister, position)
    , mMediumCrate(colliderRegister, position)
    , mLargeCrate(colliderRegister, position)
    , mDirectionArrowTexture("resources/Textures/arrow-up.png")
    , mDirectionArrowPointingUpwardCrates(mDirectionArrowTexture)
    , mTrainingLogoTexture("resources/Textures/static-muscle-training.png")
    , mTrainingLogo(mTrainingLogoTexture)
    , mTargetManager(colliderRegister, {0, 0, -2}, sf::seconds(0.75), sf::seconds(0.75))
{
    mLargeCrate.setScale(1.5);
    mMediumCrate.setScale(1);
    mSmallerCrate.setScale(0.5);
    mAABB.colliderTag(ColliderTag::Solid);
    setPosition(mPosition);
    mSmallerCrate.setRotation({90, 0, 0});
    mMediumCrate.setRotation({90, 0, 0});
    mLargeCrate.setRotation({90, 0, 0});
    mDirectionArrowPointingUpwardCrates.setRotation({-30, 25, 0});
    mDirectionArrowPointingUpwardCrates.setScale(0.6);
    mTrainingLogo.setRotation({180, 0, 0});
    mTrainingLogo.setScale(3.f);
    auto halfOfShootingRangeDimensions = mShootingRange.dimensions() / 2.f;
    mTargetManager.setSpawnRange(
        {-halfOfShootingRangeDimensions.x, -halfOfShootingRangeDimensions.y, 0},
        {halfOfShootingRangeDimensions.x, halfOfShootingRangeDimensions.y, 0});
    mButtonStand.onClick(
        [this]()
        {
            toggleShootingRange();
        });
}

void ShootingRange::draw(const Renderer& target, const Camera& camera) const
{
    mShootingRange.draw(target, camera);
    mButtonStand.draw(target, camera);
    mAABB.draw(target, camera);
    mLargeCrate.draw(target, camera);
    mMediumCrate.draw(target, camera);
    mSmallerCrate.draw(target, camera);
    mDirectionArrowPointingUpwardCrates.draw(target, camera);
    mTargetManager.draw(target, camera);
    mTrainingLogo.draw(target, camera);
}

void ShootingRange::update(const float& deltaTime)
{
    mButtonStand.update(deltaTime);
    mTargetManager.update(deltaTime);
}

void ShootingRange::handleEvent(const sf::Event& event)
{
    mButtonStand.handleEvent(event);
}

void ShootingRange::showDebugImGui(std::string name)
{
    name = "[Model] " + name;
    ImGui::Begin(name.c_str());
    ImGui::SliderFloat3("Position", &mPosition[0], -50, 50.f);
    ImGui::End();
    setPosition(mPosition);
}

void ShootingRange::setPosition(const glm::vec3& newPosition)
{
    mShootingRange.setPosition(newPosition + glm::vec3{0, 0, BOXES_DISTANCE});
    mTargetManager.setPosition(
        newPosition + glm::vec3{0, mShootingRange.dimensions().y / 2.f, BOXES_DISTANCE - 0.25f});
    mButtonStand.setPosition(newPosition + glm::vec3{-1.15, 1.5, 0.45});
    mAABB.setPosition(mShootingRange.position() - mShootingRange.dimensions() / 2.f);
    mLargeCrate.setPosition(newPosition + glm::vec3{0, 0, 0});
    mMediumCrate.setPosition(newPosition + glm::vec3{0, 0, -1.25});
    mSmallerCrate.setPosition(newPosition + glm::vec3{0, 0, -2});
    mDirectionArrowPointingUpwardCrates.setPosition(newPosition + glm::vec3{1, 0, -2.5});
    mTrainingLogo.setPosition(newPosition + glm::vec3{-0.5, 5, BOXES_DISTANCE});
}

void ShootingRange::toggleShootingRange()
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
