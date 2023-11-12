#pragma once
#include "Renderer3D/Shader.h"

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

private:
    Shader mInfiniteGridShader;
};