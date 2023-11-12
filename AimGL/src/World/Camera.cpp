#include "Camera.h"
#include "pch.h"

#include "Utils/Mouse.h"
#include <SFML/Window/Keyboard.hpp>

Camera::Camera(const WindowToRender& target)
    : mRenderTarget(target)
{
    mViewMatrix = glm::lookAt(mCameraPosition, mCameraPosition + mCameraFront, mCameraUp);

    auto targetSize = mRenderTarget.getSize();
    mProjectionMatrix = glm::perspective(
        glm::radians(0.0f), static_cast<float>(targetSize.x / targetSize.y), 1.f, 100.f);
}

void Camera::update(const float& deltaTime)
{
    handleMouseInputs(deltaTime);

    auto width = static_cast<float>(mRenderTarget.getSize().x);
    auto height = static_cast<float>(mRenderTarget.getSize().y);
    mProjectionMatrix = glm::perspective(glm::radians(mFovCamera), width / height, 0.1f, 10000.f);
    mViewMatrix = glm::lookAt(mCameraPosition, mCameraPosition + mCameraFront, mCameraUp);
}

void Camera::fixedUpdate(const float& deltaTime)
{
    handleKeyboardInputs(deltaTime);
}

void Camera::handleMouseInputs(const float& deltaTime)
{
    if (Mouse::isMouseLocked() && mAreControlsEnabled)
    {
        calculateCameraAngles(deltaTime);
        keepNaturalPitchRanges();
        calculateCameraDirectionVector();
    }
}

void Camera::calculateCameraDirectionVector()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    direction.y = sin(glm::radians(mPitch));
    direction.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mCameraFront = glm::normalize(direction);

    direction.x = cos(glm::radians(mYaw));
    direction.y = 0;
    direction.z = sin(glm::radians(mYaw));
    mCameraFrontWithoutPitch = glm::normalize(direction);
}

void Camera::calculateCameraAngles(const float& deltaTime)
{
    auto mouseOffset = static_cast<sf::Vector2f>(Mouse::mouseOffset());

    mouseOffset.x *= mCameraSensitivity * deltaTime;
    mouseOffset.y *= mCameraSensitivity * deltaTime * -1;

    mYaw += mouseOffset.x;
    mPitch += mouseOffset.y;
}

void Camera::keepNaturalPitchRanges()
{
    if (mPitch > 89.0f)
    {
        mPitch = 89.0f;
    }
    if (mPitch < -89.0f)
    {
        mPitch = -89.0f;
    }
}

void Camera::handleKeyboardInputs(const float& deltaTime)
{
    auto cameraSpeed = this->mCameraSpeed;
    cameraSpeed = applyAdditionalCameraAcceleration(cameraSpeed);
    handleCameraMovement(deltaTime, cameraSpeed);
}

void Camera::handleCameraMovement(const float& deltaTime, float cameraSpeed)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        mCameraPosition += cameraSpeed * mCameraFront * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        mCameraPosition -= cameraSpeed * mCameraFront * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        mCameraPosition +=
            glm::normalize(glm::cross(mCameraFront, mCameraUp)) * cameraSpeed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        mCameraPosition -=
            glm::normalize(glm::cross(mCameraFront, mCameraUp)) * cameraSpeed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        mCameraPosition -= cameraSpeed * mCameraUp * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        mCameraPosition += cameraSpeed * mCameraUp * deltaTime;
    }
}

float Camera::applyAdditionalCameraAcceleration(float cameraSpeed) const
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        cameraSpeed *= 2;
    }
    return cameraSpeed;
}

void Camera::handleEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::MouseWheelMoved: mFovCamera -= event.mouseWheel.delta; break;
    }
}

glm::mat4 Camera::view() const
{
    return mViewMatrix;
}

glm::mat4 Camera::projection() const
{
    return mProjectionMatrix;
}

glm::vec3 Camera::cameraPosition() const
{
    return mCameraPosition;
}

void Camera::updateImGui()
{
    ImGui::Begin("Camera");
    ImGui::SliderFloat3("Translation", &mCameraPosition.x, 0.0f, 960.0f);
    ImGui::End();
}

glm::vec3 Camera::direction() const
{
    return mCameraFront;
}

glm::vec3 Camera::rightDirection() const
{
    return glm::cross(mCameraFront, mCameraUp);
}

glm::vec3 Camera::rightDirectionWithoutPitch() const
{
    return glm::cross(mCameraFrontWithoutPitch, mCameraUp);
}

glm::vec3 Camera::upwardDirection() const
{
    return mCameraUp;
}

void Camera::cameraPosition(const glm::vec3& newPosition)
{
    mCameraPosition = newPosition;
}

glm::vec3 Camera::directionWithoutPitch() const
{
    return mCameraFrontWithoutPitch;
}

void Camera::toggleControls()
{
    mAreControlsEnabled = !mAreControlsEnabled;
}