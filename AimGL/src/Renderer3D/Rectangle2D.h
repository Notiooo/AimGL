#pragma once
#include "BufferLayout.h"
#include "Renderer3D.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

/**
 * \brief A representation of a 2d colored rectangle that has its own transformation.
 * This should be used to draw a 2d object on the screen, not in game space.
 */
class Rectangle2D
{
public:
    /**
     * \brief Determines the point that defines the root of the rectangle position.
     *
     * For example, setting Origin to Center and setting the position to
     * point (0,0) makes the rectangle's center at point (0,0).
     */
    enum class Origin
    {
        LeftBottom,
        Center
    };

    /**
     * \brief Constructs a 2D rectangle.
     * \param size Dimensions of the rectangle given in pixels.
     * \param color Rectangle color (red, green, blue, transparency).
     */
    Rectangle2D(const glm::vec2 size, const glm::vec4& color);

    /**
     * \brief Draws a rectangle to a given target
     * \param target The target to which the rectangle is drawn
     */
    void draw(const Renderer3D& target) const;

    /**
     * \brief Sets the position of the rectangle on the screen
     * \param newPosition New position to which the rectangle will be set
     * \param origin Relative to which origin the rectangle will be located
     */
    void setPosition(const glm::vec2& newPosition, Origin origin = Origin::LeftBottom);

    /**
     * \brief Rotates the rectangle
     * \param angle The angle by which the rectangle is to be rotated
     */
    void setRotation(float angle);

    /**
     * \brief Sets the transparency of the rectangle in range 0 - 1
     * \param opacity New rectangle transparency in the range of 0 - 1
     */
    void setOpacity(float opacity);

    /**
     * \brief Sets the new color of the rectangle
     * \param color Rectangle color (red, green, blue, transparency).
     */
    void setColor(glm::vec4 color);

    /**
     * \brief Sets the width of the rectangle while the aspect ratio remains preserved
     * \param width New rectangle width
     */
    void setWidth(float width);

    /**
     * \brief Sets the height of the rectangle while the aspect ratio remains preserved
     * \param height New rectangle height
     */
    void setHeight(float height);

    /**
     * \brief Displays a debug ImGui window that allows to change the internal
     * variables of the rectangle.
     * \param name Optional name of the rectangle (it can be seen in the window name).
     */
    void showDebugImGui(std::string name = "");

    /**
     * \brief Returns the opacity value of the rectangle.
     * \return Opacity of the rectangle
     */
    float opacity() const;

private:
    /**
     * \brief Updates the model in the shader (model of MVP)
     */
    void updateModel();

    /**
     * \brief Updates color information in the shader
     */
    void updateColor() const;

    /**
     * \brief Prepares buffers to work
     */
    void initializeBuffers();

private:
    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mEBO;
    Shader mShader;
    BufferLayout mBufferLayout;
    glm::vec4 mColor;
    glm::vec3 mPosition;
    glm::vec2 mDimensions;
    float mRotation;
};
