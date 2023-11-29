#pragma once
#include "Renderer/Core/Shader.h"

namespace sf
{
class Window;
}

class Camera;

/**
 * \brief An infinite floor consisting of a grid.
 * Drawn at height 0 it spreads into the other axes infinitely
 * giving the floor to the player to walk on.
 */
class InfiniteGridFloor
{
public:
    InfiniteGridFloor();

    /**
     * \brief Draws the infinite floor for a given target
     * \param target The target to which the sprite is drawn
     * \param camera A camera in 3D space that looks at this floor
     */
    void draw(sf::Window& target, const Camera& camera) const;

    /**
     * \brief Displays a debug ImGui window that allows to change the internal
     * variables of the Infinite Grid.
     * \param name Optional name of the Infinite grid (it can be seen in the window name).
     */
    void showDebugImGui(std::string name = "");

private:
    Shader mInfiniteGridShader;
    float mFar = 5.f;
};