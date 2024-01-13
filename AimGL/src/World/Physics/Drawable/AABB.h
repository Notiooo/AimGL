#pragma once
#include "Renderer/Core/Buffers/BufferLayout.h"
#include "Renderer/Core/Buffers/IndexBuffer.h"
#include "Renderer/Core/Buffers/VertexBuffer.h"
#include "Renderer/Core/Shader.h"
#include "Renderer/Core/VertexArray.h"
#include "World/Physics/Drawable/DrawableCollider.h"
#include "World/Physics/RectangleCollider.h"
#include <Renderer/Graphics/3D/Utils/Rotation3D.h>

class Camera;
class Renderer;

/**
 * \brief Axis-Aligned Bounding Box (AABB) with drawable and collision detection capabilities.
 */
class AABB final : public DrawableCollider<RectangleCollider>
{
public:
    /**
     * \brief Constructs an Axis-Aligned Bounding Box (AABB) collider.
     * \param colliderRegister Reference to the collision register for tracking this collider.
     * \param min The minimum corner point of the AABB in 3D space.
     * \param max The maximum corner point of the AABB in 3D space.
     */
    AABB(ColliderRegister& colliderRegister, const glm::vec3& min, const glm::vec3& max);
    AABB(AABB&&) noexcept = delete;
    AABB(const AABB& rhs);
    AABB& operator=(const AABB& rhs);

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

    /**
     * \brief Gets the dimensions of the object.
     * \return 3D vector representing the object's dimensions.
     */
    glm::vec3 dimensions() const;

    /**
     * \brief Retrieves the object's collider.
     * \return Constant reference to the Collider object.
     */
    const Collider& collider() const;

    /**
     * \brief Sets the scale of the object.
     * \param scaleRatio The ratio to scale the object by.
     */
    void setScale(float scaleRatio);

    /**
     * \brief Sets the rotation of the object.
     * \param rotation The new rotation to be applied, represented as a 3D rotation.
     */
    void setRotation(const Rotation3D& rotation);

private:
    /**
     * \brief Updates buffers (e.g., the position of vertices)
     *
     * TODO: The current update is rather pointless.
     *       It is better to pass transformations to the shader
     */
    void updateBuffers();

    /**
     * \brief Updates the rotation of the object based on internal state.
     */
    void updateRotation();

    /**
     * \brief Updates the position of the object based on internal state.
     */
    void updatePosition();

    /**
     * \brief Calculates the object's new Axis-Aligned Bounding Box (AABB).
     */
    void calculateNewAABB();

    /**
     * \brief Updates the scale of the object based on internal state.
     */
    void updateScale();

    /**
     * \brief Retrieves the current rotation matrix of the object.
     * \return The current rotation matrix as a 4x4 matrix.
     */
    glm::mat4 currentRotationMatrix();

    /**
     * \brief Gets the vertices of the Axis-Aligned Bounding Box (AABB) as a vector of 3D vectors.
     * \return A vector of glm::vec3 representing the vertices of the AABB.
     */
    std::vector<glm::vec3> verticesOfAABBInFormOfVec3() const;

    /**
     * \brief Gets the vertices of the Axis-Aligned Bounding Box (AABB) as a flat vector of floats.
     * \return A vector of floats representing the vertices of the AABB.
     */
    std::vector<float> verticesOfAABBInFormOfFloats() const;

private:
    glm::vec3& mMin;
    glm::vec3& mMax;
    glm::vec3 mOriginalMin{};
    glm::vec3 mOriginalMax{};
    Rotation3D mRotation{0, 0, 0};
    float mScale{1};
    glm::vec3 mPosition{0, 0, 0};

    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mEBO;
    BufferLayout mBufferLayout;
    Shader mShader;
};
