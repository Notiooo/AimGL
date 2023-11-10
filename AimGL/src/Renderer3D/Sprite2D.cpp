#include "Sprite2D.h"
#include "pch.h"

Sprite2D::Sprite2D(const Texture& texture)
    : mTexture(texture)
    , mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Sprite.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Sprite.fs"}}
    , mPosition(0.0f)
    , mScale(1.0f)
    , mRotation(0.f)
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
    // Prepare transformations
    mShader.bind();
    mTexture.bind(0);
    target.draw(mVAO, mEBO, mShader);
}

void Sprite2D::updateModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mPosition));
    model = glm::rotate(model, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(mScale, 1.0f));
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

void Sprite2D::setScale(float newScale)
{
    mScale = {mTexture.width(), mTexture.height()};
    mScale *= newScale;
}

void Sprite2D::setRotation(float angle)
{
    mRotation = angle;
}

void Sprite2D::setOpacity(float opacity)
{
    mOpacity = opacity;
    mShader.bind();
    mShader.setUniform("opacity", mOpacity);
    mShader.unbind();
}

void Sprite2D::setWidth(float width)
{
    mScale = {width, width / mTexture.aspectRatio()};
    mScale /= 2.f;
    updateModel();
}

void Sprite2D::setHeight(float height)
{
    mScale = {height * mTexture.aspectRatio(), height};
    mScale /= 2.f;
    updateModel();
}
