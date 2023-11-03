#include "Renderer3D.h"
#include "pch.h"

void Renderer3D::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                      const DrawMode& drawMode) const
{
    shader.bind();
    va.bind();
    ib.bind();
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
