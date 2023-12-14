#include "Ray.h"
#include "pch.h"

#include "Renderer/Renderer.h"

Ray::Ray(ColliderRegister& colliderRegister, const glm::vec3& origin, const glm::vec3& direction,
         float length)
    : DrawableCollider(colliderRegister, origin, direction, length)
    , mOrigin(mCollider.origin)
    , mDirection(mCollider.direction)
    , mLength(mCollider.length)
    , mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Physics/Ray.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Physics/Ray.fs"}}
{
    glm::vec3 endPoint = mOrigin + mDirection * mLength;

    std::vector<float> vertices = {mOrigin.x,  mOrigin.y,  mOrigin.z,
                                   endPoint.x, endPoint.y, endPoint.z};
    mBufferLayout.push<float>(3);

    mVBO.setBuffer(vertices);
    mVAO.setBuffer(mVBO, mBufferLayout);
}

void Ray::draw(const Renderer& target, const Camera& camera) const
{
    constexpr auto numberOfVertices = 6;
    target.draw3D(mVAO, numberOfVertices, mShader, camera, Renderer::DrawMode::Lines);
}
