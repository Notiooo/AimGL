#pragma once

#include "Renderer3D/BufferLayout.h"
#include "Renderer3D/IndexBuffer.h"
#include "Renderer3D/Renderer3D.h"
#include "Renderer3D/Shader.h"
#include "Renderer3D/Texture.h"
#include "Renderer3D/VertexArray.h"
#include "States/State.h"

class StateStack;

/**
 * \brief  ....
 */
class SampleState : public State
{
public:
    SampleState(StateStack& stack, sf::Window& window);

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
    Renderer3D render3D;
    Texture mLogo;
    VertexArray mVao;
    VertexBuffer mVbo;
    IndexBuffer mEbo;
    BufferLayout mBufferLayout;
    Shader mShader;
};
