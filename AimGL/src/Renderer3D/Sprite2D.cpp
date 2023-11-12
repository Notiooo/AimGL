#include "Sprite2D.h"
#include "pch.h"

Sprite2D::Sprite2D(const Texture& texture)
    : mTexture(texture)
    , mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Sprite.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Sprite.fs"}}
    , mPosition(0.0f)
    , mScale(1.0f)
    , mRotation(0.f)
    , mDimensions({mTexture.width(), mTexture.height()})
{

    initializeBuffers();
    setScale(1);
    setPosition({0.f, 0.f});
}

void Sprite2D::initializeBuffers()
{
    float vertices[] = {
        // positions    // texture coords
        1.f,  1.f,  1.0f, 1.0f,// top right
        1.f,  -1.f, 1.0f, 0.0f,// bottom right
        -1.f, -1.f, 0.0f, 0.0f,// bottom left
        -1.f, 1.f,  0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3,// first Triangle
        1, 2, 3 // second Triangle
    };

    mVBO.setBuffer(vertices, sizeof(vertices));
    mEBO.setBuffer(indices, sizeof(indices));

    mVAO.bind();
    mVBO.bind();
    mBufferLayout.push<float>(2);
    mBufferLayout.push<float>(2);
    mVAO.setBuffer(mVBO, mBufferLayout);
    mVAO.unbind();
}

void Sprite2D::draw(const Renderer3D& target) const
{
    mShader.bind();
    mTexture.bind(0);
    target.draw(mVAO, mEBO, mShader);
}

void Sprite2D::updateModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mPosition));

    // Negative mRotation makes it rotate clockwise for positive angles
    model = glm::rotate(model, glm::radians(-mRotation), glm::vec3(0.0f, 0.0f, 1.0f));

    // Dividing dimensions by two is needed as vertices are from -1 to 1
    model = glm::scale(model, glm::vec3(mDimensions * mScale / 2.f, 1.0f));
    mShader.bind();
    mShader.setUniform("model", model);
    mShader.unbind();
}

void Sprite2D::setPosition(const glm::vec2& newPosition, Origin origin)
{
    switch (origin)
    {
        case Origin::Center: mPosition = glm::vec3(newPosition, 0.f); break;
        case Origin::LeftBottom:
            mPosition = glm::vec3(newPosition, 0.f);
            mPosition += glm::vec3{mTexture.width(), mTexture.height(), 0.f};
            break;
    }
    updateModel();
}

void Sprite2D::showDebugImGui(std::string name)
{
    name = "[Sprite2D] " + name;
    ImGui::Begin(name.c_str());
    ImGui::SliderFloat2("Position", &mPosition[0], -1500.f, 1500.f);
    ImGui::SliderFloat2("Dimensions", &mDimensions[0], -0.f, 1500.f);
    ImGui::SliderFloat("Rotation", &mRotation, 0.0f, 360.f);
    ImGui::SliderFloat("Scale", &mScale, -1.0f, 10.0f);
    ImGui::SliderFloat("Opacity", &mOpacity, 0.0f, 1.0f);
    ImGui::End();
    updateModel();
    updateOpacity();
}

void Sprite2D::setScale(float newScale)
{
    mScale = newScale;
    updateModel();
}

void Sprite2D::setRotation(float angle)
{
    mRotation = angle;
    updateModel();
}

void Sprite2D::updateOpacity() const
{
    mShader.bind();
    mShader.setUniform("opacity", mOpacity);
    mShader.unbind();
}

void Sprite2D::setOpacity(float opacity)
{
    mOpacity = opacity;
    updateOpacity();
}

void Sprite2D::setWidth(float width)
{
    mDimensions = {width, width / mTexture.aspectRatio()};
    updateModel();
}

void Sprite2D::setHeight(float height)
{
    mDimensions = {height * mTexture.aspectRatio(), height};
    updateModel();
}
