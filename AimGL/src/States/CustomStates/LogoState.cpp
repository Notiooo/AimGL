#include "LogoState.h"
#include "States/StateStack.h"
#include "pch.h"

LogoState::LogoState(StateStack& stack, sf::Window& window)
    : State(stack)
    , mWindow(window)
    , mLogoTexture("resources/Textures/logo.png")
    , mLogo(mLogoTexture)
    , mRenderer3D(window)
    , mPhase(Phase::FadeIn)
{
    mClock.restart();
    mLogo.setPosition(glm::vec2(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f),
                      Sprite2D::Origin::Center);
    mLogo.setHeight(mWindow.getSize().y);
    mLogo.setOpacity(0);
}

void LogoState::draw(sf::Window& target) const
{
    MTR_SCOPE("SampleState", "SampleState::draw");
    mLogo.draw(mRenderer3D);
}

bool LogoState::fixedUpdate(const float& deltaTime)
{
    MTR_SCOPE("SampleState", "SampleState::fixedUpdate");
    return true;
}

bool LogoState::update(const float& deltaTime)
{
    MTR_SCOPE("SampleState", "SampleState::update");
    switch (mPhase)
    {
        case Phase::FadeIn:
            mLogo.setOpacity((mClock.getElapsedTime().asSeconds() / 2.f) - 0.2f);
            if (mClock.getElapsedTime().asSeconds() > 3.f)
            {
                mPhase = Phase::Fadeout;
                mClock.restart();
            }
            break;

        case Phase::Fadeout:
            mLogo.setOpacity(2.f - mClock.getElapsedTime().asSeconds() / 2.f);
            if (mClock.getElapsedTime().asSeconds() > 4.f)
            {
                requestPop();
                requestPush(State_ID::ExitGameState);
            }
            break;
    }
    return true;
}

bool LogoState::handleEvent(const sf::Event& event)
{
    MTR_SCOPE("SampleState", "SampleState::handleEvent");
    return true;
}

bool LogoState::updateImGui(const float& deltaTime)
{
    MTR_SCOPE("SampleState", "SampleState::updateImGui");
    ImGui::ShowDemoWindow();
    return true;
}
