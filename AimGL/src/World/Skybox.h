#pragma once
#include "Renderer/Core/Buffers/BufferLayout.h"
#include "Renderer/Core/Shader.h"
#include "Renderer/Core/VertexArray.h"

class Camera;

class Skybox
{
public:
    /**
     * \brief Constructor for the Skybox class, initializes the skybox environment.
     */
    Skybox();

    /**
     * \brief Destructor for the Skybox class.
     */
    ~Skybox();

    /**
     * \brief Binds the skybox's textures and resources for rendering.
     */
    void bind() const;

    /**
     * \brief Unbinds the skybox's textures and resources.
     */
    void unbind() const;

    /**
     * \brief Draws the skybox using a camera's perspective.
     * \param camera The camera viewing the skybox.
     */
    void draw(const Camera& camera) const;

private:
    /**
     * \brief Retrieves the file paths of the skybox's face textures.
     * \return Vector of strings representing paths to skybox face textures.
     */
    std::vector<std::string> skyboxFacesTextures();

    /**
     * \brief Provides the vertices for the skybox.
     * \return Vector of floats representing the skybox vertices.
     */
    std::vector<float> skyboxVertices();

    /**
     * \brief Determines the image format for texture loading.
     * \return The GLenum representing the image format.
     */
    GLenum deduceImageFormat();

    /**
     * \brief Loads a texture of one face of the skybox. TODO: Make it more readable
     * \param faces The texture file paths for the skybox faces.
     * \param faceId The ID of the face to which the texture is applied.
     */
    void loadTextureFace(const std::vector<std::string>& faces, unsigned faceId);

private:
    unsigned int mTextureId;
    float mAspectRatio;
    int mWidth, mHeight, mNrChannels;

    VertexArray mVAO;
    VertexBuffer mVBO;
    BufferLayout mBufferLayout;
    Shader mShader;
};
