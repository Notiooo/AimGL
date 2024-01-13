#include "ButtonStand.h"
#include "pch.h"

ButtonStand::ButtonStand(ColliderRegister& colliderRegister, const glm::vec3& position)
    : mButtonStand("resources/Models/button_stand/button-stand.obj",
                   {{"resources/Models/button_stand/button-stand.png", Texture::Type::Diffuse}})
    , mColliderRegister(colliderRegister)
    , mCollisionBox(mColliderRegister, {0, 0, 0}, mButtonStand.dimensions())
    , mButtonShotTriggerBox(
          colliderRegister, {0, 0, 0},
          {mButtonStand.dimensions().x / 2.f, 0.1, mButtonStand.dimensions().z / 2.f})
{
    mSoundBuffer.loadFromFile("resources/Sounds/button-click.wav");
    mClickSound.setBuffer(mSoundBuffer);
    setPosition(position);
    mCollisionBox.colliderTag(ColliderTag::Solid);

    mButtonShotTriggerBox.callback(
        [this](const Collider& collider)
        {
            if (collider.colliderTag() == ColliderTag::GunShot)
            {
                if (not isAnimationBeingPlayed)
                {
                    signalizeButtonClick();
                    mOnShotFunction();
                }
            }
        });
}

void ButtonStand::draw(const Renderer& target, const Camera& camera) const
{
    mButtonStand.draw(target, camera);
    mCollisionBox.draw(target, camera);
    mButtonShotTriggerBox.draw(target, camera);
}

void ButtonStand::update(const float& deltaTime)
{
    if (isAnimationBeingPlayed)
    {
        if (mAnimationClock.getElapsedTime() > mTimeOfClickAnimation)
        {
            isAnimationBeingPlayed = false;
            mButtonStand.mesh().setTexture(
                {"resources/Models/button_stand/button-stand.png", Texture::Type::Diffuse});
        }
    }
}

void ButtonStand::onClick(std::function<void()> onShotFunction)
{
    mOnShotFunction = std::move(onShotFunction);
}

void ButtonStand::handleEvent(const sf::Event& event)
{
    // TODO: Meh... I think it is unexpected to check
    // whether mouse is clicked :/

    if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left &&
        not isAnimationBeingPlayed)
    {
        hasNewMouseClickOccured = true;
    }
}

void ButtonStand::setPosition(const glm::vec3& newPosition)
{
    mButtonStand.setPosition(newPosition);
    mCollisionBox.setPosition(mButtonStand.position() - mButtonStand.dimensions() / 2.f);
    auto shotTriggerBoxPosition = mButtonStand.position();
    shotTriggerBoxPosition.x -= mButtonStand.dimensions().x / 4.f;
    shotTriggerBoxPosition.z -= mButtonStand.dimensions().z / 4.f;
    shotTriggerBoxPosition.y += (mButtonStand.dimensions().y / 2.f) - 0.1;
    mButtonShotTriggerBox.setPosition(shotTriggerBoxPosition);
}

void ButtonStand::signalizeButtonClick()
{
    if (hasNewMouseClickOccured)
    {
        isAnimationBeingPlayed = true;
        mAnimationClock.restart();
        mButtonStand.mesh().setTexture(
            {"resources/Models/button_stand/button-stand-clicked.png", Texture::Type::Diffuse});
        hasNewMouseClickOccured = false;
        mClickSound.play();
    }
}
