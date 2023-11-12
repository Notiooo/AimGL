#include "Sprite3D.h"
#include "Utils/Normalize.h"
#include "World/Camera.h"
#include "pch.h"

Sprite3D::Sprite3D(const Texture& texture)
    : mTexture(texture)
    , mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Sprite3D.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Sprite3D.fs"}}
    , mPosition(0.0f)
    , mScale(1.0f)
    , mDimensionsNormalized()
    , mRotation(0.f, {0.f, 0.f, 1.f})
{
    auto max = static_cast<float>(std::max(mTexture.width(), mTexture.height()));
    mDimensionsNormalized = {normalize(mTexture.width(), 0, max),
                             normalize(mTexture.height(), 0, max)};

    initializeBuffers();
    setPosition({0.f, 0.f, 0.f});
}

void Sprite3D::initializeBuffers()
{
    float vertices[] = {
        // positions    // texture coords
        1.f,  1.f,  0.0f, 1.0f, 1.0f,// top right
        1.f,  -1.f, 0.0f, 1.0f, 0.0f,// bottom right
        -1.f, -1.f, 0.0f, 0.0f, 0.0f,// bottom left
        -1.f, 1.f,  0.0f, 0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3,// first Triangle
        1, 2, 3 // second Triangle
    };

    mVBO.setBuffer(vertices, sizeof(vertices));
    mEBO.setBuffer(indices, sizeof(indices));

    mVAO.bind();
    mVBO.bind();
    mBufferLayout.push<float>(3);
    mBufferLayout.push<float>(2);
    mVAO.setBuffer(mVBO, mBufferLayout);
    mVAO.unbind();
}

void Sprite3D::draw(const Renderer& target, const Camera& camera) const
{
    mShader.bind();
    mTexture.bind(0);
    target.draw3D(mVAO, mEBO, mShader, camera);
}

void Sprite3D::updateModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mPosition));
    model = glm::rotate(model, glm::radians(mRotation.first), mRotation.second);
    model = glm::scale(model, glm::vec3(mDimensionsNormalized * mScale / 2.f, 1.0f));
    mShader.bind();
    mShader.setUniform("model", model);
    mShader.unbind();
}

void Sprite3D::setPosition(const glm::vec3& newPosition, Origin origin)
{
    switch (origin)
    {
        case Origin::Center: mPosition = newPosition; break;
        case Origin::LeftBottom:
            mPosition = newPosition;
            mPosition += glm::vec3{mDimensionsNormalized.x / 2.f, mDimensionsNormalized.y / 2.f, 0};
            break;
    }
    updateModel();
}

void Sprite3D::setScale(float newScale)
{
    mScale *= newScale;
    updateModel();
}

void Sprite3D::setRotation(float angle, glm::vec3 axis)
{
    mRotation = {angle, axis};
}

void Sprite3D::updateOpacity() const
{
    mShader.bind();
    mShader.setUniform("opacity", mOpacity);
    mShader.unbind();
}

void Sprite3D::setOpacity(float opacity)
{
    mOpacity = opacity;
    updateOpacity();
}

void Sprite3D::setWidth(float width)
{
    auto newDimensions = glm::vec2{width, width / mTexture.aspectRatio()};
    auto max = static_cast<float>(std::max(newDimensions.x, newDimensions.y));
    mDimensionsNormalized = {normalize(newDimensions.x, 0, max),
                             normalize(newDimensions.y, 0, max)};
    updateModel();
}

void Sprite3D::setHeight(float height)
{
    auto newDimensions = glm::vec2{height * mTexture.aspectRatio(), height};
    auto max = static_cast<float>(std::max(newDimensions.x, newDimensions.y));
    mDimensionsNormalized = {normalize(newDimensions.x, 0, max),
                             normalize(newDimensions.y, 0, max)};
    updateModel();
}

void Sprite3D::showDebugImGui(std::string name)
{
    name = "[Sprite3D] " + name;
    ImGui::Begin(name.c_str());
    ImGui::SliderFloat3("Position", &mPosition[0], -15, 15.f);
    ImGui::SliderFloat2("Dimensions Normalized", &mDimensionsNormalized[0], 0, 2.f);
    ImGui::SliderFloat3("Rotation Axis", &mRotation.second[0], 0.0f, 1.f);
    ImGui::SliderFloat("Rotation Angle", &mRotation.first, 0.f, 360.0f);
    ImGui::SliderFloat2("Scale", &mScale[0], -4.0f, 4.0f);
    ImGui::SliderFloat("Opacity", &mOpacity, 0.0f, 1.0f);
    ImGui::End();
    updateModel();
    updateOpacity();
}
