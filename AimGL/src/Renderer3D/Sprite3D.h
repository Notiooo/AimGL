#pragma once
#include "BufferLayout.h"
#include "Renderer3D.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"


class Camera;

/**
 * \brief A representation of a texture that has its own transformations in 3D.
 * The default size of a 3D Sprite in space is a maximum of 1 in one axis.
 * The other axis maintains the aspect ratio.
 */
class Sprite3D
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
    Sprite3D(const Texture& texture);

    /**
     * \brief Draws a sprite for a given target
     * \param target The target to which the sprite is drawn
     * \param camera A camera in 3D space that looks at this object
     */
    void draw(const Renderer3D& target, const Camera& camera) const;

    /**
     * \brief Sets the position of the sprite on the screen
     * \param newPosition New position to which the sprite will be set
     * \param origin Relative to which origin the sprite will be located
     */
    void setPosition(const glm::vec3& newPosition, Origin origin = Origin::LeftBottom);

    /**
     * \brief Sets the scale at which the sprite will be drawn
     * \param newScale New scale with which the sprite will be drawn
     */
    void setScale(float newScale);

    /**
     * \brief Rotates the sprite
     * \param angle The angle by which the sprite is to be rotated
     * \param axis Axes according to which the object should rotate
     */
    void setRotation(float angle, glm::vec3 axis);

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

    /**
     * \brief Displays a debug ImGui window that allows to change the internal
     * variables of the 3d sprite.
     * \param name Optional name of the rectangle (it can be seen in the window name).
     */
    void showDebugImGui(std::string name = "");

private:
    /**
     * \brief Updates the model in the shader (model of MVP)
     */
    void updateModel();

    /**
     * \brief Updates the opacity in the shader
     */
    void updateOpacity() const;

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
    glm::vec2 mDimensionsNormalized;
    std::pair<float, glm::vec3> mRotation;
    float mOpacity;
};
