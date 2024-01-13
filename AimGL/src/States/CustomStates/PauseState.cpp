#include "PauseState.h"
#include "Utils/Mouse.h"
#include "pch.h"

PauseState::PauseState(StateStack& stack, WindowToRender& window)
    : State(stack)
    , mWindowToRender(window)
    , mRenderer(window)
    , mPauseTextTexture("resources/Textures/pause.png")
    , mPauseText(mPauseTextTexture)
    , mRectangle({window.getSize().x, window.getSize().y}, {0.f, 0.f, 0.f, 1.f})
    , mWasMouseLocked(Mouse::isMouseLocked())

{
    mPauseText.setPosition(
        glm::vec2(mWindowToRender.getSize().x / 2.f, mWindowToRender.getSize().y / 2.f),
        Sprite2D::Origin::Center);
    mPauseText.setHeight(mWindowToRender.getSize().y / 3.f);
    mRectangle.setPosition({0, 0});
    mRectangle.setOpacity(0.7f);
    Mouse::unlockMouse(window);
}

void PauseState::draw(sf::Window& target) const
{
    MTR_SCOPE("PauseState", "PauseState::draw");
    mRectangle.draw(mRenderer);
    mPauseText.draw(mRenderer);
}

bool PauseState::update(const float& deltaTime)
{
    MTR_SCOPE("PauseState", "PauseState::update");
    return false;
}

bool PauseState::fixedUpdate(const float& deltaTime)
{
    MTR_SCOPE("PauseState", "PauseState::fixedUpdate");
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    MTR_SCOPE("PauseState", "PauseState::handleEvent");
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape:
                if (mWasMouseLocked)
                {
                    Mouse::lockMouseAtCenter(mWindowToRender);
                }
                requestPop();
                break;
        }
    }
    return false;
}