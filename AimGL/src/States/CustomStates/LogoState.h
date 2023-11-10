#pragma once

#include "Renderer3D/Renderer3D.h"
#include "Renderer3D/Sprite2D.h"
#include "States/State.h"

class StateStack;

/**
 * \brief Game state drawing the game logo
 */
class LogoState : public State
{
public:
    LogoState(StateStack& stack, sf::Window& window);

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
    /**
     * \brief This state is divided into two states:
     * the state in which the logo fades in and
     * the state in which the logo fades out.
     */
    enum class Phase
    {
        FadeIn,
        Fadeout
    };

private:
    Renderer3D mRenderer3D;
    Texture mLogoTexture;
    Sprite2D mLogo;
    sf::Clock mClock;
    sf::Window& mWindow;
    Phase mPhase;
};
