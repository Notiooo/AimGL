#pragma once

#include "Renderer/Graphics/3D/Core/Vertex.h"
#include <Renderer/Core/Buffers/BufferLayout.h>
#include <Renderer/Core/Buffers/IndexBuffer.h>
#include <Renderer/Core/Shader.h>
#include <Renderer/Core/VertexArray.h>
#include <Renderer/Graphics/Texture.h>
#include <Renderer/Renderer.h>

/**
 * \brief Basic representation of shape of 3d object
 */
class Mesh
{
public:
    /**
     * \brief Constructor of Mesh class
     * \param vertices The vertices of which the shape consists
     * \param indices Indexes describing the order in which the vertices are drawn
     * \param textures Textures with which the mesh should be drawn
     */
    Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned>&& indices,
         std::vector<Texture>&& textures);

    /**
     * \brief Draws a mesh for a given target
     * \param target The target to which the mesh is drawn
     * \param camera A camera in 3D space that looks at this object
     * \param shader Shader that should be used to draw the mesh
     */
    void draw(const Renderer& target, const Camera& camera, const Shader& shader) const;

    /**
     * \brief Sets a new texture for the object.
     * \param newTexture The new texture to be applied.
     */
    void setTexture(Texture&& newTexture);

private:
    /**
     * \brief Sets the specified texture to the shader
     * \param shader Shader to which the texture should be bind
     * \param texture Texture that should be bind to shader
     */
    void setTextureToShaderUniform(const Shader& shader, const Texture& texture) const;

    /**
     * \brief Sets default values to object material in shader
     * \param shader Shader to which default values should be set
     */
    void setDefaultValuesToMaterialUniforms(const Shader& shader) const;

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;// TODO: resource manager should be used there

    VertexArray mVAO;
    VertexBuffer mVBO;
    IndexBuffer mEBO;
    BufferLayout mBufferLayout;
};
