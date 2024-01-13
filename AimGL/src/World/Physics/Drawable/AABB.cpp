#include "AABB.h"
#include "Renderer/Renderer.h"
#include "pch.h"

#include <constants.h>


std::vector<float> AABB::verticesOfAABBInFormOfFloats() const
{
    return {
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
}

void AABB::updateBuffers()
{
    const auto vertices = verticesOfAABBInFormOfFloats();
    const std::vector<unsigned int> indices = {
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
    , mOriginalMin(mCollider.min)
    , mOriginalMax(mCollider.max)
    , mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Physics/AABB.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Physics/AABB.fs"}}
    , mPosition(min)
{
    mBufferLayout.push<float>(3);
    updateBuffers();
}

AABB::AABB(const AABB& rhs)
    : DrawableCollider(rhs)
    , mMin(mCollider.min)
    , mMax(mCollider.max)
    , mOriginalMin(mCollider.min)
    , mOriginalMax(mCollider.max)
    , mRotation(rhs.mRotation)
    , mScale(rhs.mScale)
    , mPosition(rhs.mPosition)
    , mShader{rhs.mShader.filePaths()}
{
    mBufferLayout.push<float>(3);
    updateBuffers();
}

AABB& AABB::operator=(const AABB& rhs)
{
    if (&rhs != this)
    {
        mMin = rhs.mMin;
        mMax = rhs.mMax;
        mOriginalMin = rhs.mOriginalMin;
        mOriginalMax = rhs.mOriginalMax;
        mRotation = rhs.mRotation;
        mScale = rhs.mScale;
        mPosition = rhs.mPosition;
        updateBuffers();
    }
    return *this;
}

void AABB::draw(const Renderer& target, const Camera& camera) const
{
    if (DRAW_COLLIDERS)
    {
        target.draw3D(mVAO, mEBO, mShader, camera, Renderer::DrawMode::Lines);
    }
}

void AABB::setPosition(const glm::vec3& position)
{
    mPosition = position;
    calculateNewAABB();
}

glm::vec3 AABB::dimensions() const
{
    return mMax - mMin;
}

const Collider& AABB::collider() const
{
    return mCollider;
}

void AABB::setScale(float scaleRatio)
{
    mScale = scaleRatio;
    calculateNewAABB();
}

void AABB::setRotation(const Rotation3D& rotation)
{
    mRotation = rotation;
    calculateNewAABB();
}

glm::mat4 AABB::currentRotationMatrix()
{
    const auto rotX =
        glm::rotate(glm::mat4(1.0f), glm::radians(mRotation.pitch), glm::vec3(1, 0, 0));
    const auto rotY = glm::rotate(glm::mat4(1.0f), glm::radians(mRotation.yaw), glm::vec3(0, 1, 0));
    const auto rotZ =
        glm::rotate(glm::mat4(1.0f), glm::radians(mRotation.roll), glm::vec3(0, 0, 1));
    return rotY * rotX * rotZ;
}

std::vector<glm::vec3> AABB::verticesOfAABBInFormOfVec3() const
{
    return {{mMin.x, mMin.y, mMin.z}, {mMin.x, mMin.y, mMax.z}, {mMin.x, mMax.y, mMin.z},
            {mMin.x, mMax.y, mMax.z}, {mMax.x, mMin.y, mMin.z}, {mMax.x, mMin.y, mMax.z},
            {mMax.x, mMax.y, mMin.z}, {mMax.x, mMax.y, mMax.z}};
}

void AABB::updateRotation()
{
    auto mOldMin = mMin;
    auto mOldMax = mMax;
    auto dims = mMax - mMin;
    mMin = glm::vec3{0.f, 0.f, 0.f} - dims / 2.f;
    mMax = glm::vec3{0.f, 0.f, 0.f} + dims / 2.f;
    glm::vec3 originalCenter = (mOldMin + mOldMax) * 0.5f;
    auto translation = originalCenter;

    glm::vec3 newMin(std::numeric_limits<float>::max());
    glm::vec3 newMax(std::numeric_limits<float>::lowest());

    // Rotate each vertex and adjust newMin and newMax accordingly
    auto rotationMatrix = currentRotationMatrix();
    for (auto& vertex: verticesOfAABBInFormOfVec3())
    {
        glm::vec4 rotated = rotationMatrix * glm::vec4(vertex, 1.0f);
        newMin = glm::min(newMin, glm::vec3(rotated));
        newMax = glm::max(newMax, glm::vec3(rotated));
    }
    mMin = newMin + translation;
    mMax = newMax + translation;
}

void AABB::updatePosition()
{
    auto diff = mMax - mMin;
    mMin += mPosition;// bug there ??
    mMax = mMin + diff;
}

void AABB::updateScale()
{
    mMin *= mScale;
    mMax *= mScale;
}

void AABB::calculateNewAABB()
{
    mMin = mOriginalMin;
    mMax = mOriginalMax;
    updateScale();
    updateRotation();
    updatePosition();
    updateBuffers();
}
