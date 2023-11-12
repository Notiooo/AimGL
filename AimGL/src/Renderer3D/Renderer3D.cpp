#include "Renderer3D.h"
#include "World/Camera.h"
#include "pch.h"

Renderer3D::Renderer3D(sf::Window& window)
    : mWindow(window)
{
}

void Renderer3D::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                      const DrawMode& drawMode) const
{
    shader.bind();
    va.bind();
    ib.bind();

    glm::mat4 windowOrthoProjection = glm::ortho(0.f, static_cast<float>(mWindow.getSize().x), 0.f,
                                                 static_cast<float>(mWindow.getSize().y));
    shader.setUniform("windowOrthoProjection", windowOrthoProjection);

    glDisable(GL_DEPTH_TEST);
    GLCall(glDrawElements(toOpenGl(drawMode), ib.size(), GL_UNSIGNED_INT, nullptr));
    glEnable(GL_DEPTH_TEST);

#ifdef _DEBUG
    shader.unbind();
    va.unbind();
    ib.unbind();
#endif
}

void Renderer3D::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                      const Camera& camera, const DrawMode& drawMode) const
{
    shader.bind();
    va.bind();
    ib.bind();

    const auto view = camera.view();
    const auto projection = camera.projection();
    shader.setUniform("view", view);
    shader.setUniform("projection", projection);
    GLCall(glDrawElements(toOpenGl(drawMode), ib.size(), GL_UNSIGNED_INT, nullptr));

#ifdef _DEBUG
    shader.unbind();
    va.unbind();
    ib.unbind();
#endif
}

unsigned Renderer3D::toOpenGl(const Renderer3D::DrawMode& drawMode) const
{
    switch (drawMode)
    {
        case DrawMode::Lines: return GL_LINES;
        case DrawMode::Triangles: return GL_TRIANGLES;
        case DrawMode::Quads: return GL_QUADS;
        default: throw std::runtime_error("This DrawMode is not supported!");
    }
}
