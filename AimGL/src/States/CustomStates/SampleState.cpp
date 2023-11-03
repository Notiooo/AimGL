#include "SampleState.h"
#include "pch.h"

float verticestest[] = {
    0.5f,  0.5f,  0.0f,// top right
    0.5f,  -0.5f, 0.0f,// bottom right
    -0.5f, -0.5f, 0.0f,// bottom left
    -0.5f, 0.5f,  0.0f // top left
};
unsigned int indicestest[] = {
    // note that we start from 0!
    0, 1, 3,// first Triangle
    1, 2, 3 // second Triangle
};

SampleState::SampleState(StateStack& stack, sf::Window& window)
    : State(stack)
    , mShader{{ShaderType::VertexShader, "resources/Shaders/basic.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/basic.fs"}}
{
    mVbo.setBuffer(verticestest, sizeof(verticestest));
    mEbo.setBuffer(indicestest, sizeof(indicestest));
    mBufferLayout.push<float>(3);
    mVao.setBuffer(mVbo, mBufferLayout);
}

void SampleState::draw(sf::Window& target) const
{
    MTR_SCOPE("SampleState", "SampleState::draw");
    render3D.draw(mVao, mEbo, mShader);
}

bool SampleState::fixedUpdate(const float& deltaTime)
{
    MTR_SCOPE("SampleState", "SampleState::fixedUpdate");
    return true;
}

bool SampleState::update(const float& deltaTime)
{
    MTR_SCOPE("SampleState", "SampleState::update");
    return true;
}

bool SampleState::handleEvent(const sf::Event& event)
{
    MTR_SCOPE("SampleState", "SampleState::handleEvent");
    return true;
}

bool SampleState::updateImGui(const float& deltaTime)
{
    MTR_SCOPE("SampleState", "SampleState::updateImGui");
    ImGui::ShowDemoWindow();
    return true;
}
