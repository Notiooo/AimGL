#include "Rectangle2D.h"
#include "pch.h"

Rectangle2D::Rectangle2D(const glm::vec2 size, const glm::vec4& color)
    : mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Rectangle2D.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Rectangle2D.fs"}}
    , mColor(color)
    , mPosition(0.0f)
    , mRotation(0.f)
    , mDimensions(size)
{

    initializeBuffers();
    setPosition({0.f, 0.f}, Origin::Center);

    updateColor();
}

void Rectangle2D::initializeBuffers()
{
    float vertices[] = {
        // positions
        1.f,  1.f, // top right
        1.f,  -1.f,// bottom right
        -1.f, -1.f,// bottom left
        -1.f, 1.f  // top left
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
    mVAO.setBuffer(mVBO, mBufferLayout);
    mVAO.unbind();
}

void Rectangle2D::draw(const Renderer& target) const
{
    target.draw2D(mVAO, mEBO, mShader);
}

void Rectangle2D::updateColor() const
{
    mShader.bind();
    mShader.setUniform("color", mColor);
    mShader.unbind();
}

void Rectangle2D::updateModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mPosition));

    // Negative mRotation makes it rotate clockwise for positive angles
    model = glm::rotate(model, glm::radians(-mRotation), glm::vec3(0.0f, 0.0f, 1.0f));

    // Dividing dimensions by two is needed as vertices are from -1 to 1
    model = glm::scale(model, glm::vec3(mDimensions / 2.f, 1.0f));
    mShader.bind();
    mShader.setUniform("model", model);
    mShader.unbind();
}

void Rectangle2D::setPosition(const glm::vec2& newPosition, Origin origin)
{
    switch (origin)
    {
        case Origin::Center: mPosition = glm::vec3(newPosition, 0.f); break;
        case Origin::LeftBottom:
            mPosition = glm::vec3(newPosition, 0.f);
            mPosition += glm::vec3{mDimensions.x / 2.f, mDimensions.y / 2.f, 0.f};
            break;
    }
    updateModel();
}

void Rectangle2D::setColor(glm::vec4 color)
{
    mColor = color;
    updateColor();
}

void Rectangle2D::setRotation(float angle)
{
    mRotation = angle;
    updateModel();
}

void Rectangle2D::setOpacity(float opacity)
{
    mColor.a = opacity;
    updateColor();
}

void Rectangle2D::setWidth(float width)
{
    mDimensions.x = width;
    updateModel();
}

void Rectangle2D::setHeight(float height)
{
    mDimensions.y = height;
    updateModel();
}

void Rectangle2D::showDebugImGui(std::string name)
{
    name = "[Rectangle2D] " + name;
    ImGui::Begin(name.c_str());
    ImGui::SliderFloat4("Color", &mColor[0], 0.0f, 1.0f);
    ImGui::SliderFloat2("Position", &mPosition[0], -1500.f, 1500.f);
    ImGui::SliderFloat("Rotation", &mRotation, 0.0f, 360.f);
    ImGui::End();
    updateModel();
    updateColor();
}

float Rectangle2D::opacity() const
{
    return mColor.a;
}
