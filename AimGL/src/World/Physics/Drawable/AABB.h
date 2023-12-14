#pragma once
#include "Renderer/Core/Buffers/BufferLayout.h"
#include "Renderer/Core/Buffers/IndexBuffer.h"
#include "Renderer/Core/Buffers/VertexBuffer.h"
#include "Renderer/Core/Shader.h"
#include "Renderer/Core/VertexArray.h"
#include "World/Physics/Drawable/DrawableCollider.h"
#include "World/Physics/RectangleCollider.h"

class Camera;
class Renderer;
class ColliderRegister;

/**
 * \brief Axis-Aligned Bounding Box (AABB) with drawable and collision detection capabilities.
 */
class AABB : public DrawableCollider<RectangleCollider>
{
public:
    /**
     * \brief Constructs an Axis-Aligned Bounding Box (AABB) collider.
     * \param colliderRegister Reference to the collision register for tracking this collider.
     * \param min The minimum corner point of the AABB in 3D space.
     * \param max The maximum corner point of the AABB in 3D space.
     */
    AABB(ColliderRegister& colliderRegister, const glm::vec3& min, const glm::vec3& max);
    AABB(AABB&&) noexcept = default;

    /**
     * \brief Draws a AABB for a given target
     * \param target The target to which the AABB is drawn
     * \param camera A camera in 3D space that looks at this object
     */
    void draw(const Renderer& target, const Camera& camera) const;

    /**
     * Updates the AABB logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void update(const float& deltaTime);

    /**
     * \brief Sets the new AABB position
     * \param position new position
     */
    void setPosition(const glm::vec3& position);

private:
    /**
     * \brief Updates buffers (e.g., the position of vertices)
     *
     * TODO: The current update is rather pointless.
     *       It is better to pass transformations to the shader
     */
    void updateBuffers();

private:
    glm::vec3& mMin;
    glm::vec3& mMax;

    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mEBO;
    BufferLayout mBufferLayout;
    Shader mShader;
};
