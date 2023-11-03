#pragma once

#include "Renderer3D/IndexBuffer.h"
#include "Renderer3D/Shader.h"
#include "Renderer3D/VertexArray.h"

/**
 * 3D Renderer allows to draw 3D objects to the screen using appropriate buffers and shaders
 */
class Renderer3D
{
public:
    enum class DrawMode
    {
        Lines,
        Triangles,
        Quads
    };

    /**
     * Draws the data given in VertexArray, IndexBuffer to the screen using the interpretation given
     * in Shader.
     * @param va Stores all Vertex Data.
     * @param ib Specifies the drawing order of the VertexArray.
     * @param shader Shader telling how to draw data.
     */
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
              const DrawMode& drawMode = DrawMode::Triangles) const;

private:
    unsigned toOpenGl(const DrawMode& drawMode) const;
};