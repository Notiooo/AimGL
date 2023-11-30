#include "Player.h"
#include "Utils/Lerp.h"
#include "pch.h"

Player::Player(WindowToRender& window)
    : mCamera(window)
    , mGun("resources/Models/ak47/ak47.obj",
           {{"resources/Models/ak47/ak47-alternative.png", Texture::Type::Diffuse},
            {"resources/Models/ak47/ak47-alternative-specular.png", Texture::Type::Specular}})
    , mCrosshairTexture("resources/Textures/crosshair.png")
    , mCrosshair(mCrosshairTexture)
{
    mCrosshair.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f},
                           Sprite2D::Origin::Center);
    mCrosshair.setOpacity(0.8f);
    mCamera.cameraPosition({mPosition.x, mPosition.y + PLAYER_HEGIHT, mPosition.z});
    mGun.setPosition(mCamera.cameraPosition(), Model::Origin::Center);
}

void Player::draw(const Renderer& target) const
{
    glDepthRange(0.0, 0.01);
    mGun.draw(target, mCamera);
    glDepthRange(0.0, 1.0);

    mCrosshair.draw(target);
}

void Player::updateGunPosition(const float& deltaTime)
{
    const glm::vec3 rotationOrigin = {0.3f, -0.2f, -0.35f};
    const glm::vec3 targetPosition = {mPosition.x + rotationOrigin.x,
                                      mPosition.y + PLAYER_HEGIHT * 5 / 8,
                                      mPosition.z + rotationOrigin.z};

    const auto gunPosition = lerp(mGun.position(), targetPosition, deltaTime * 30.f);
    mGun.setPosition(gunPosition, Model::Origin::Center);
    mGun.setRotationOrigin(rotationOrigin);

    const auto gunTargetPitch =
        lerp(mGun.rotation().pitch, mCamera.rotation().pitch, deltaTime * 20.f);
    const auto gunTargetYaw =
        lerp(mGun.rotation().yaw, -(mCamera.rotation().yaw + 90), deltaTime * 20.f);
    mGun.setRotation({gunTargetYaw, gunTargetPitch, 0});
}

void Player::update(const float& deltaTime)
{
    mCamera.cameraPosition({mPosition.x, mPosition.y + PLAYER_HEGIHT, mPosition.z});
    mCamera.update(deltaTime);
    updateGunPosition(deltaTime);
}

void Player::updatePhysics(float deltaTime)
{
    handleMovementKeyboardInputs(deltaTime);
    decelerateVelocity(deltaTime);
    manageVerticalVelocity(deltaTime);
    limitVelocity(deltaTime);

    mPosition += mVelocity;
    if (mPosition.y < 0)
    {
        mPosition.y = 0;
    }
}

void Player::decelerateVelocity(const float& deltaTime)
{
    float decayFactor = exp(-PLAYER_WALKING_DECELERATE_RATIO * deltaTime);
    mVelocity.x *= decayFactor;
    mVelocity.z *= decayFactor;
}

void Player::manageVerticalVelocity(const float& deltaTime)
{
    constexpr auto G = -9.81f * 0.01f;
    mVelocity.y += G * deltaTime;
}

void Player::limitVelocity(const float& deltaTime)
{
    static auto limitVelocitySpeed = [](auto& velocity, const auto& maxVelocity)
    {
        if (velocity > maxVelocity)
        {
            velocity = maxVelocity;
        }
        else if (-velocity > maxVelocity)
        {
            velocity = -maxVelocity;
        }
    };

    auto playerVelocity = PLAYER_MAX_HORIZONTAL_SPEED * deltaTime;
    limitVelocitySpeed(mVelocity.x, playerVelocity);
    limitVelocitySpeed(mVelocity.z, playerVelocity);


    if (-mVelocity.y > PLAYER_MAX_FALLING_SPEED)
    {
        mVelocity.y = -PLAYER_MAX_FALLING_SPEED;
    }
}

void Player::fixedUpdate(const float& deltaTime)
{
    updatePhysics(deltaTime);
}

void Player::handleMovementKeyboardInputs(const float& deltaTime)
{
    auto ACCELERATION_RATIO = 0.1f;
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        direction += mCamera.directionWithoutPitch();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        direction -= mCamera.directionWithoutPitch();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        direction += mCamera.rightDirectionWithoutPitch();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        direction -= mCamera.rightDirectionWithoutPitch();
    }

    if (glm::length(direction) > 0.0f)
    {
        direction = glm::normalize(direction);// Normalize the combined direction
        const auto finalSpeed = PLAYER_WALKING_SPEED * ACCELERATION_RATIO * deltaTime;
        mVelocity += finalSpeed * direction;
    }
}

void Player::tryJump()
{
    if (isOnGround())
    {
        mVelocity.y = PLAYER_JUMP_FORCE;
    }
}

void Player::handleEvent(const sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Space: tryJump(); break;
    }
}

Camera& Player::camera()
{
    return mCamera;
}

const Camera& Player::camera() const
{
    return mCamera;
}

bool Player::isOnGround() const
{
    return mPosition.y <= 0;
}
