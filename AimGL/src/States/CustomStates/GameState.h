#pragma once

#include "Renderer/Graphics/2D/Rectangle2D.h"
#include "Renderer/Graphics/3D/Sprite3D.h"
#include "Renderer/Renderer.h"
#include "States/State.h"
#include "World/Camera.h"
#include "World/InfiniteGridFloor.h"

#include <Player/Player.h>
#include <Renderer/Graphics/3D/Model.h>
#include <World/Physics/ColliderRegister.h>
#include <World/Scene/GameObjects/PreviewTarget.h>

class StateStack;

/**
 * \brief The game state in which all the action of the game (player training) takes place.
 */
class GameState : public State
{
public:
    GameState(StateStack& stack, WindowToRender& window);

    /**
     * \brief Draws only this state to the passed target
     * \param target where it should be drawn to
     */
    void draw(sf::Window& target) const override;


    /**
     * \brief Updates the state logic at equal intervals independent of the frame rate.
     * \param deltaTime Time interval
     */
    bool fixedUpdate(const float& deltaTime) override;

    /**
     * \brief Updates the game logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    bool update(const float& deltaTime) override;

    /**
     * \brief It takes input (event) from the user and interprets it
     * \param event user input
     */
    bool handleEvent(const sf::Event& event) override;

    /**
     * \brief Updates the imgui logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    bool updateImGui(const float& deltaTime) override;

private:
    WindowToRender& mWindow;
    ColliderRegister mColliderRegister;
    Player mPlayer;
    Renderer mRenderer;
    Texture mLogoTexture;
    Sprite3D mLogo;
    Rectangle2D mGameBackground;
    sf::Clock mPhaseInClock;
    Rectangle2D mPhaseInLogoColor;
    InfiniteGridFloor mInfiniteGridFloor;
    Model mTree;
    std::vector<std::unique_ptr<PreviewTarget>> mPreviewTargets;
};
