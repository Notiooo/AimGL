#include "InfiniteGridFloor.h"
#include "pch.h"

#include "World/Camera.h"


InfiniteGridFloor::InfiniteGridFloor()
    : mInfiniteGridShader{
          {ShaderType::VertexShader, "resources/Shaders/Graphics/InfiniteGridFloor.vs"},
          {ShaderType::FragmentShader, "resources/Shaders/Graphics/InfiniteGridFloor.fs"}}
{
}

void InfiniteGridFloor::draw(sf::Window& target, const Camera& camera) const
{
    mInfiniteGridShader.bind();
    const auto view = camera.view();
    const auto projection = camera.projection();
    mInfiniteGridShader.setUniform("view", view);
    mInfiniteGridShader.setUniform("projection", projection);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    mInfiniteGridShader.unbind();
}

void InfiniteGridFloor::showDebugImGui(std::string name)
{
    name = "[InfiniteGridFloor] " + name;
    ImGui::Begin(name.c_str());
    ImGui::SliderFloat("Far", &mFar, 0.0f, 5.f);
    ImGui::End();
    mInfiniteGridShader.bind();
    mInfiniteGridShader.setUniform("far", mFar);
    mInfiniteGridShader.unbind();
}
