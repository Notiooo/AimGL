#include "GameState.h"
#include "Renderer/Graphics/3D/Sprite3D.h"
#include "States/StateStack.h"
#include "Utils/Mouse.h"
#include "pch.h"

GameState::GameState(StateStack& stack, WindowToRender& window)
    : State(stack)
    , mWindow(window)
    , mRenderer(mWindow)
    , mLogoTexture("resources/Textures/logo_background.png")
    , mLogo(mLogoTexture)
    , mCamera(window)
    , mGameBackground(glm::vec2(1280, 720.f), glm::vec4(0.85f, 0.85f, 0.85f, 1.f))
    , mPhaseInLogoColor({window.getSize().x, window.getSize().y}, {0.067f, 0.11f, 0.18f, 1.1f})
    , tree("resources/Models/tree/tree.obj",
           {{"resources/Models/tree/tree_combined.png", Texture::Type::Diffuse}})
{
    Mouse::lockMouseAtCenter(mWindow);
    mLogo.setHeight(2.f);
    mLogo.setPosition(glm::vec3(0, 0, 0), Sprite3D::Origin::LeftBottom);
    mLogo.setOpacity(1);
    mGameBackground.setPosition({0, 0});
    mPhaseInLogoColor.setPosition({0, 0});
    mPhaseInClock.restart();
    mCamera.cameraPosition({1, 1.5, 2});
}

void GameState::draw(sf::Window& target) const
{
    MTR_SCOPE("GameState", "GameState::draw");
    mGameBackground.draw(mRenderer);
    mInfiniteGridFloor.draw(target, mCamera);
    tree.draw(mRenderer, mCamera);
    mLogo.draw(mRenderer, mCamera);
    mPhaseInLogoColor.draw(mRenderer);
}

bool GameState::fixedUpdate(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::fixedUpdate");
    mCamera.fixedUpdate(deltaTime);
    return true;
}

bool GameState::update(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::update");
    mCamera.update(deltaTime);

    if (mPhaseInLogoColor.opacity() > 0)
    {
        mPhaseInLogoColor.setOpacity(mPhaseInLogoColor.opacity() - deltaTime / 4.f);
    }
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    MTR_SCOPE("GameState", "GameState::handleEvent");
    mCamera.handleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape: Mouse::unlockMouse(mWindow); break;
        }
    }
    return true;
}

bool GameState::updateImGui(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::updateImGui");
    mCamera.updateImGui();
    mInfiniteGridFloor.showDebugImGui();
    ImGui::ShowDemoWindow();
    return true;
}
