#include "GameState.h"
#include "Renderer/Graphics/3D/Sprite3D.h"
#include "States/StateStack.h"
#include "Utils/Mouse.h"
#include "pch.h"

#include <Player/Player.h>
#include <constants.h>

GameState::GameState(StateStack& stack, WindowToRender& window)
    : State(stack)
    , mWindow(window)
    , mPlayer(window, mColliderRegister)
    , mRenderer(mWindow)
    , mPhaseInLogoColor({window.getSize().x, window.getSize().y}, {0.067f, 0.11f, 0.18f, 1.1f})
    , mShootingRange(mColliderRegister, {-2, 0, 5.5})
    , mSidewayMovingTargetsRange(mColliderRegister, {3, 0, 5.5})
    , mWelcomeScreenTexture("resources/Textures/welcome-screen.png")
    , mWelcomeScreen(mWelcomeScreenTexture)
{
    Mouse::lockMouseAtCenter(mWindow);
    mWelcomeScreen.setScale(2);
    mWelcomeScreen.setPosition({0, 1, -2}, Sprite3D::Origin::Center);
    mPhaseInLogoColor.setPosition({0, 0});
    mPhaseInClock.restart();
}

void GameState::draw(sf::Window& target) const
{
    MTR_SCOPE("GameState", "GameState::draw");
    mSkybox.draw(mPlayer.camera());
    mInfiniteGridFloor.draw(target, mPlayer.camera());
    mWelcomeScreen.draw(mRenderer, mPlayer.camera());
    mPhaseInLogoColor.draw(mRenderer);
    mShootingRange.draw(mRenderer, mPlayer.camera());
    mSidewayMovingTargetsRange.draw(mRenderer, mPlayer.camera());
    mPlayer.draw(mRenderer);
}

bool GameState::fixedUpdate(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::fixedUpdate");
    mColliderRegister.updateAllCollisions();
    mPlayer.fixedUpdate(deltaTime);
    return true;
}

bool GameState::update(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::update");
    mPlayer.update(deltaTime);
    mShootingRange.update(deltaTime);
    mSidewayMovingTargetsRange.update(deltaTime);

    if (mPhaseInLogoColor.opacity() > 0)
    {
        mPhaseInLogoColor.setOpacity(mPhaseInLogoColor.opacity() - deltaTime / 4.f);
    }
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    MTR_SCOPE("GameState", "GameState::handleEvent");
    Mouse::handleFirstPersonBehaviour(event, mWindow);
    if (not Mouse::isMouseLocked())
    {
        return true;
    }

    mPlayer.handleEvent(event);
    mShootingRange.handleEvent(event);
    mSidewayMovingTargetsRange.handleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Escape: requestPush(State_ID::PauseState); break;
            case sf::Keyboard::F1: switchWireframe(); break;
            case sf::Keyboard::F2: switchDrawingColliders(); break;
            case sf::Keyboard::F3: switchDrawingImgui(); break;
            case sf::Keyboard::F4: Mouse::unlockMouse(mWindow); break;
        }
    }
    return true;
}

void GameState::switchWireframe()
{
    std::unique_ptr<int[]> rastMode(new int[2]);
    GLCall(glGetIntegerv(GL_POLYGON_MODE, rastMode.get()));

    if (rastMode[1] == GL_FILL)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void GameState::switchDrawingColliders()
{
#ifdef _DEBUG
    DRAW_COLLIDERS = !DRAW_COLLIDERS;
#endif
}

void GameState::switchDrawingImgui()
{
    mDrawImgui = !mDrawImgui;
}

void GameState::updateImguiDebugMenu()
{
    if (ImGui::BeginMenu("Debug menu"))
    {
        if (ImGui::MenuItem("Switch Wireframe (on/off)"))
        {
            switchWireframe();
        }

        if (ImGui::MenuItem("Toggle colliders draw"))
        {
            switchDrawingColliders();
        }

        if (ImGui::MenuItem("Toggle imgui draw"))
        {
            switchDrawingImgui();
        }
        ImGui::EndMenu();
    }
}

void GameState::updateImGuiDebugInstructionText()
{
    auto windowWidth = ImGui::GetWindowSize().x;
    auto debugInfoText = "F1 - Wireframe | F2 - Toggle colliders draw | F3 - Toggle imgui draw";
    auto textWidth = ImGui::CalcTextSize(debugInfoText).x;
    auto margin = 10.f;

    ImGui::SetCursorPosX(windowWidth - textWidth - margin);
    ImGui::Text(debugInfoText);
    ImGui::EndMainMenuBar();
}

bool GameState::updateImGui(const float& deltaTime)
{
    MTR_SCOPE("GameState", "GameState::updateImGui");
    if (mDrawImgui)
    {
        if (ImGui::BeginMainMenuBar())
        {
            updateImguiDebugMenu();
            updateImGuiDebugInstructionText();
        }
    }
    return true;
}
