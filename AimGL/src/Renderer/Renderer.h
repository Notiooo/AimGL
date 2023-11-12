#pragma once

#include "Renderer/Core/Buffers/IndexBuffer.h"
#include "Renderer/Core/Shader.h"
#include "Renderer/Core/VertexArray.h"

class Camera;

/**
 * Renderer allows to draw 3D and 2D objects to the screen using appropriate buffers and shaders
 */
class Renderer
{
public:
    enum class DrawMode
    {
        Lines,
        Triangles,
        Quads
    };

    explicit Renderer(sf::Window& window);

    /**
     * Draws the data given in VertexArray, IndexBuffer to the screen using the interpretation given
     * in Shader.
     * @param va Stores all Vertex Data.
     * @param ib Specifies the drawing order of the VertexArray.
     * @param shader Shader telling how to draw data.
     */
    void draw2D(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                const DrawMode& drawMode = DrawMode::Triangles) const;

    void draw3D(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                const Camera& camera, const DrawMode& drawMode = DrawMode::Triangles) const;

private:
    unsigned toOpenGl(const DrawMode& drawMode) const;
    sf::Window& mWindow;
};