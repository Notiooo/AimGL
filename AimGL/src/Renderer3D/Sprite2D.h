#pragma once
#include "BufferLayout.h"
#include "Renderer3D.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

/**
 * \brief A representation of a texture that has its own transformation.
 */
class Sprite2D
{
public:
    /**
     * \brief Determines the point that defines the root of the sprite's position.
     *
     * For example, setting Origin to Center and setting the position to
     * point (0,0) makes the sprite's center at point (0,0).
     */
    enum class Origin
    {
        LeftBottom,
        Center
    };

    /**
     * \brief Constructs a sprite from the given texture.
     * \param texture Texture from which the sprite is to be created
     */
    Sprite2D(const Texture& texture);

    /**
     * \brief Draws a sprite for a given target
     * \param target The target to which the sprite is drawn
     */
    void draw(const Renderer3D& target) const;

    /**
     * \brief Sets the position of the sprite on the screen
     * \param newPosition New position to which the sprite will be set
     * \param origin Relative to which origin the sprite will be located
     */
    void setPosition(const glm::vec2& newPosition, Origin origin = Origin::LeftBottom);

    /**
     * \brief Sets the scale at which the sprite will be drawn
     * \param newScale New scale with which the sprite will be drawna
     */
    void setScale(float newScale);

    /**
     * \brief Rotates the sprite
     * \param angle The angle by which the sprite is to be rotated
     */
    void setRotation(float angle);

    /**
     * \brief Sets the transparency of the sprite in range 0 - 1
     * \param opacity New sprite transparency in the range of 0 - 1
     */
    void setOpacity(float opacity);

    /**
     * \brief Sets the width of the sprite while the aspect ratio remains preserved
     * \param width New sprite width
     */
    void setWidth(float width);

    /**
     * \brief Sets the height of the sprite while the aspect ratio remains preserved
     * \param height New sprite height
     */
    void setHeight(float height);

private:
    /**
     * \brief Updates the model in the shader (model of MVP)
     */
    void updateModel();

    /**
     * \brief Prepares buffers to work
     */
    void initializeBuffers();

private:
    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mEBO;
    const Texture& mTexture;
    Shader mShader;
    BufferLayout mBufferLayout;
    glm::vec3 mPosition;
    glm::vec2 mScale;
    float mRotation;
    float mOpacity;
};
