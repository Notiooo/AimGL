#pragma once
#include "Renderer/Core/Buffers/BufferLayout.h"
#include "Renderer/Core/Buffers/VertexBuffer.h"
#include "Renderer/Core/Shader.h"
#include "Renderer/Core/VertexArray.h"
#include "World/Physics/Drawable/DrawableCollider.h"
#include "World/Physics/RayCollider.h"

class Camera;
class Renderer;

/**
 * \brief Represents a ray in 3D space, defined by an origin point, direction vector, and length.
 */
class Ray : public DrawableCollider<RayCollider>
{
public:
    /**
     * \brief Constructs a Ray object.
     * \param colliderRegister Reference to the collision register for tracking this collider.
     * \param origin The starting point of the ray in 3D space.
     * \param direction The direction vector of the ray. This vector should be normalized.
     * \param length (Optional) The length of the ray. Default is 100 units.
     */
    Ray(ColliderRegister& colliderRegister, const glm::vec3& origin, const glm::vec3& direction,
        float length = 100);
    Ray(Ray&&) noexcept = default;

    /**
     * \brief Draws a Ray for a given target
     * \param target The target to which the model is drawn
     * \param camera A camera in 3D space that looks at this object
     */
    void draw(const Renderer& target, const Camera& camera) const;

    /**
     * Updates the Ray logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void update(const float& deltaTime);

private:
    glm::vec3& mOrigin;
    glm::vec3& mDirection;
    float& mLength;
    VertexArray mVAO;
    VertexBuffer mVBO;
    BufferLayout mBufferLayout;
    Shader mShader;
};
