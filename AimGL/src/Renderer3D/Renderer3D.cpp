#include "Renderer3D.h"
#include "pch.h"

void GLClearError()
{
    while (glGetError() /* != GL_NO_ERROR*/)
    {
        ;
    }
}

bool GLLogCall(const char* function, const char* file, int line)
{
    if (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << "): " << function
                  << " " << file << " at line: " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer3D::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                      const DrawMode& drawMode) const
{
    // shader.bind();
    va.bind();
    ib.bind();
    GLCall(glDrawElements(toOpenGL(drawMode), ib.size(), GL_UNSIGNED_INT, nullptr));

#ifdef _DEBUG
    // shader.bind();
    va.unbind();
    ib.unbind();
#endif
}

unsigned Renderer3D::toOpenGL(const Renderer3D::DrawMode& drawMode) const
{
    switch (drawMode)
    {
        case DrawMode::Lines: return GL_LINES;
        case DrawMode::Triangles: return GL_TRIANGLES;
        case DrawMode::Quads: return GL_QUADS;
        default: throw std::runtime_error("This DrawMode is not supported!");
    }
}
