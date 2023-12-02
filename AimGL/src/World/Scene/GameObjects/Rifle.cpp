#include "Rifle.h"
#include "pch.h"

#include <Utils/Lerp.h>
#include <World/Camera.h>

Rifle::Rifle(Camera& camera)
    : mCamera(camera)
    , mGun("resources/Models/ak47/ak47.obj",
           {{"resources/Models/ak47/ak47-alternative.png", Texture::Type::Diffuse},
            {"resources/Models/ak47/ak47-alternative-specular.png", Texture::Type::Specular}})
{
    mSoundBuffer.loadFromFile("resources/Sounds/gunshot.wav");
    mGunShotSound.setBuffer(mSoundBuffer);
}

void Rifle::draw(const Renderer& target) const
{
    glDepthRange(0.0, 0.01);
    mGun.draw(target, mCamera);
    glDepthRange(0.0, 1.0);
    if (mLatelyShotRay.has_value())
    {
        mLatelyShotRay.value().draw(target, mCamera);
    }
}

void Rifle::update(const float& deltaTime)
{
    updateAttachToCamera(deltaTime);
}

void Rifle::updateAttachToCamera(const float& deltaTime)
{
    auto backward = -mCamera.direction();
    auto recoilOffset = backward * mCurrentRecoil;

    const glm::vec3 rotationOrigin = {0.3f, -0.2f, -0.35f};
    const auto cameraPosition = mCamera.cameraPosition();
    glm::vec3 targetPosition = {cameraPosition.x + rotationOrigin.x, cameraPosition.y - 0.3f,
                                cameraPosition.z + rotationOrigin.z};

    targetPosition += recoilOffset;

    const auto gunPosition = lerp(mGun.position(), targetPosition, deltaTime * 30.f);
    mGun.setPosition(gunPosition, Model::Origin::Center);
    mGun.setRotationOrigin(rotationOrigin);

    const auto gunTargetPitch =
        lerp(mGun.rotation().pitch, mCamera.rotation().pitch, deltaTime * 20.f);
    const auto gunTargetYaw =
        lerp(mGun.rotation().yaw, -(mCamera.rotation().yaw + 90), deltaTime * 20.f);
    mGun.setRotation({gunTargetYaw, gunTargetPitch, 0});

    mCurrentRecoil -= deltaTime;
    mCurrentRecoil = std::max(mCurrentRecoil, 0.0f);
}

void Rifle::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
    {
        mCurrentRecoil += RECOIL_OFFSET_INCREMENT;
        mCurrentRecoil = std::min(mCurrentRecoil, RECOIL_OFFSET_MAX);
        mCamera.shake();
        mGunShotSound.play();
        mLatelyShotRay.emplace(mCamera.cameraPosition(), mCamera.direction());
    }
}