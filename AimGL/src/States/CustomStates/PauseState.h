#pragma once
#include "States/State.h"

#include "Game.h"
#include "Renderer/Graphics/2D/Rectangle2D.h"
#include "Renderer/Graphics/2D/Sprite2D.h"
#include "Renderer/Graphics/Texture.h"

class StateStack;

/**
 * @brief The state in which the player pauses the game
 */
class PauseState : public State
{
public:
    PauseState(StateStack& stack, WindowToRender& window);

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

private:
    WindowToRender& mWindowToRender;
    Renderer mRenderer;
    Texture mPauseTextTexture;
    Sprite2D mPauseText;
    Rectangle2D mRectangle;
    bool mWasMouseLocked;
};