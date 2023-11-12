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
