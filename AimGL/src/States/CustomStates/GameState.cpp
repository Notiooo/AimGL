#include "GameState.h"
#include "Renderer/Graphics/3D/Sprite3D.h"
#include "States/StateStack.h"
#include "Utils/Mouse.h"
#include "pch.h"

#include <Player/Player.h>

GameState::GameState(StateStack& stack, WindowToRender& window)
    : State(stack)
    , mWindow(window)
    , mPlayer(window, mColliderRegister)
    , mRenderer(mWindow)
    , mLogoTexture("resources/Textures/logo_background.png")
    , mLogo(mLogoTexture)
    , mGameBackground(glm::vec2(1280, 720.f), glm::vec4(0.85f, 0.85f, 0.85f, 1.f))
    , mPhaseInLogoColor({window.getSize().x, window.getSize().y}, {0.067f, 0.11f, 0.18f, 1.1f})
    , mTree("resources/Models/tree/tree.obj",
            {{"resources/Models/tree/tree_combined.png", Texture::Type::Diffuse}})
{
    Mouse::lockMouseAtCenter(mWindow);
    mTree.setScale(0.2f);
    mTree.setPosition({4, 0, 4}, Model::Origin::CenterBottom);
    mLogo.setHeight(2.f);
    mLogo.setPosition(glm::vec3(4, 0, 4), Sprite3D::Origin::LeftBottom);
    mLogo.setRotation({225.f, 0.f, 0});
    mLogo.setOpacity(1);
    mGameBackground.setPosition({0, 0});
    mPhaseInLogoColor.setPosition({0, 0});
    mPhaseInClock.restart();
}

void GameState::draw(sf::Window& target) const
{
    MTR_SCOPE("GameState", "GameState::draw");
    mGameBackground.draw(mRenderer);
    mInfiniteGridFloor.draw(target, mPlayer.camera());
    mTree.draw(mRenderer, mPlayer.camera());
    mLogo.draw(mRenderer, mPlayer.camera());
    mPhaseInLogoColor.draw(mRenderer);
    mPlayer.draw(mRenderer);
}

bool GameState::fixedUpdate(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::fixedUpdate");
    mPlayer.fixedUpdate(deltaTime);
    mColliderRegister.updateAllCollisions();
    return true;
}

bool GameState::update(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::update");
    mPlayer.update(deltaTime);

    if (mPhaseInLogoColor.opacity() > 0)
    {
        mPhaseInLogoColor.setOpacity(mPhaseInLogoColor.opacity() - deltaTime / 4.f);
    }
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    MTR_SCOPE("GameState", "GameState::handleEvent");
    mPlayer.handleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape: Mouse::unlockMouse(mWindow); break;
        }
    }
    Mouse::handleFirstPersonBehaviour(event, mWindow);
    return true;
}

bool GameState::updateImGui(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::updateImGui");
    mInfiniteGridFloor.showDebugImGui();
    mLogo.showDebugImGui("Logo");
    mTree.showDebugImGui("Tree");
    return true;
}
