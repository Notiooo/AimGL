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

    std::vector<glm::vec3> samplePreviewTargetsPositons = {
        {2, 2, 2}, {2, 1, 2}, {2, 3, 2}, {2.5, 2, 2.6}, {3, 3, 3},
        {3, 2, 1}, {1, 2, 3}, {0, 3, 2}, {0, 1, 1},     {0, 2, 4}};
    for (auto& position: samplePreviewTargetsPositons)
    {
        auto test = std::make_unique<PreviewTarget>(mColliderRegister, position);
        mPreviewTargets.push_back(std::move(test));
    }
}

void GameState::draw(sf::Window& target) const
{
    MTR_SCOPE("GameState", "GameState::draw");
    mGameBackground.draw(mRenderer);
    mInfiniteGridFloor.draw(target, mPlayer.camera());
    mTree.draw(mRenderer, mPlayer.camera());
    mLogo.draw(mRenderer, mPlayer.camera());
    mPhaseInLogoColor.draw(mRenderer);

    for (auto& previewTarget: mPreviewTargets)
    {
        previewTarget->draw(mRenderer, mPlayer.camera());
    }
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
    for (auto& previewTarget: mPreviewTargets)
    {
        previewTarget->update(deltaTime);
    }
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
            case sf::Keyboard::F1: switchWireframe(); break;
            case sf::Keyboard::F2: switchDrawingColliders(); break;
            case sf::Keyboard::F3: switchDrawingImgui(); break;
        }
    }
    Mouse::handleFirstPersonBehaviour(event, mWindow);
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
        mInfiniteGridFloor.showDebugImGui();
    }
    return true;
}
