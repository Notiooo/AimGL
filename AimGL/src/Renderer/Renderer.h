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
     * \brief Draws the data given in VertexArray, IndexBuffer to the screen using
     * the interpretation given in Shader.
     * @param va Stores all Vertex Data.
     * @param ib Specifies the drawing order of the VertexArray.
     * @param shader Shader telling how to draw data.
     */
    void draw2D(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                const DrawMode& drawMode = DrawMode::Triangles) const;

    /**
     * \brief Draws the data given in VertexArray, IndexBuffer to the screen using
     * the interpretation given in Shader. In additon information about view, projection
     * and position are passed to the shader from camera.
     * \param va Vertex array containing the object's vertices.
     * \param ib Index buffer defining the order to draw the vertices.
     * \param shader Shader program to apply during rendering.
     * \param camera Camera object defining the view and projection matrices.
     * \param drawMode (Optional) Specifies the mode of drawing (e.g., triangles, lines).
     */
    void draw3D(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                const Camera& camera, const DrawMode& drawMode = DrawMode::Triangles) const;

    /**
     * \brief Draws the data given in VertexArray with specified number of vertices to
     *  the screen using the interpretation given in Shader. In additon information about
     *  view, projection and position are passed to the shader from camera.
     *  \param va Vertex array containing the object's vertices.
     * \param numberOfVertices Number of vertices to draw.
     * \param shader Shader program to use during rendering.
     * \param camera Camera object for view and projection.
     * \param drawMode Specifies the drawing mode (e.g., points, lines).
     */
    void draw3D(const VertexArray& vb, int numberOfVertices, const Shader& shader,
                const Camera& camera, const DrawMode& drawMode) const;

private:
    /**
     * \brief Convert a DrawMode enum value to the corresponding OpenGL mode.
     * \param drawMode DrawMode enum value.
     * \return Corresponding OpenGL drawing mode (e.g., GL_TRIANGLES).
     */
    unsigned toOpenGl(const DrawMode& drawMode) const;

    sf::Window& mWindow;
};