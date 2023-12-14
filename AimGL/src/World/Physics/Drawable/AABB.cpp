#include "AABB.h"
#include "pch.h"

#include "Renderer/Renderer.h"

void AABB::updateBuffers()
{
    std::vector<float> vertices = {
        // 8 corners of the AABB
        mMin.x, mMin.y, mMin.z,// 0: Bottom-back-left
        mMax.x, mMin.y, mMin.z,// 1: Bottom-back-right
        mMin.x, mMax.y, mMin.z,// 2: Top-back-left
        mMax.x, mMax.y, mMin.z,// 3: Top-back-right
        mMin.x, mMin.y, mMax.z,// 4: Bottom-front-left
        mMax.x, mMin.y, mMax.z,// 5: Bottom-front-right
        mMin.x, mMax.y, mMax.z,// 6: Top-front-left
        mMax.x, mMax.y, mMax.z,// 7: Top-front-right
    };

    std::vector<unsigned int> indices = {
        // Each pair of indices represents one line segment
        0, 1, 1, 5, 5, 4, 4, 0,// Bottom rectangle
        2, 3, 3, 7, 7, 6, 6, 2,// Top rectangle
        0, 2, 1, 3, 4, 6, 5, 7 // Connecting edges
    };

    mVBO.setBuffer(vertices);
    mEBO.setBuffer(indices);
    mVAO.setBuffer(mVBO, mBufferLayout);
}

AABB::AABB(ColliderRegister& colliderRegister, const glm::vec3& min, const glm::vec3& max)
    : DrawableCollider(colliderRegister, min, max)
    , mMin(mCollider.min)
    , mMax(mCollider.max)
    , mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Physics/AABB.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Physics/AABB.fs"}}
{
    mBufferLayout.push<float>(3);
    updateBuffers();
}

void AABB::draw(const Renderer& target, const Camera& camera) const
{
    target.draw3D(mVAO, mEBO, mShader, camera, Renderer::DrawMode::Lines);
}

void AABB::setPosition(const glm::vec3& position)
{
    auto diff = mMax - mMin;
    mMin = position;
    mMax = mMin + diff;
    updateBuffers();
}
