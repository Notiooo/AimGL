#include "Skybox.h"
#include "pch.h"

#include "World/Camera.h"

Skybox::Skybox()
    : mTextureId(0)
    , mWidth(0)
    , mHeight(0)
    , mNrChannels(0)
    , mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Skybox.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Skybox.fs"}}
{
    auto vertices = skyboxVertices();

    mBufferLayout.push<float>(3);
    mVBO.setBuffer(vertices);
    mVAO.setBuffer(mVBO, mBufferLayout);

    auto faces = skyboxFacesTextures();
    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
    for (auto i = 0; i < faces.size(); i++)
    {
        loadTextureFace(faces, i);
    }
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

Skybox::~Skybox()
{
    GLCall(glDeleteTextures(1, &mTextureId));
}

void Skybox::bind() const
{
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId));
}

void Skybox::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

void Skybox::draw(const Camera& camera) const
{
    glDepthMask(GL_FALSE);
    constexpr auto numberOfVertices = 36;
    mShader.bind();
    mVAO.bind();
    bind();
    const auto view = glm::mat4(glm::mat3(camera.view()));
    const auto projection = camera.projection();
    mShader.setUniform("view", view);
    mShader.setUniform("projection", projection);
    GLCall(glDrawArrays(GL_TRIANGLES, 0, numberOfVertices));
    glDepthMask(GL_TRUE);
}

std::vector<std::string> Skybox::skyboxFacesTextures()
{
    return {"resources/Textures/Skybox/right.jpg",  "resources/Textures/Skybox/left.jpg",
            "resources/Textures/Skybox/bottom.jpg", "resources/Textures/Skybox/top.jpg",
            "resources/Textures/Skybox/front.jpg",  "resources/Textures/Skybox/back.jpg"};
}

std::vector<float> Skybox::skyboxVertices()
{
    return {
        // positions
        -1.0f, 1.0f,  -1.0f,//
        -1.0f, -1.0f, -1.0f,//
        1.0f,  -1.0f, -1.0f,//
        1.0f,  -1.0f, -1.0f,//
        1.0f,  1.0f,  -1.0f,//
        -1.0f, 1.0f,  -1.0f,//

        -1.0f, -1.0f, 1.0f, //
        -1.0f, -1.0f, -1.0f,//
        -1.0f, 1.0f,  -1.0f,//
        -1.0f, 1.0f,  -1.0f,//
        -1.0f, 1.0f,  1.0f, //
        -1.0f, -1.0f, 1.0f, //

        1.0f,  -1.0f, -1.0f,//
        1.0f,  -1.0f, 1.0f, //
        1.0f,  1.0f,  1.0f, //
        1.0f,  1.0f,  1.0f, //
        1.0f,  1.0f,  -1.0f,//
        1.0f,  -1.0f, -1.0f,//

        -1.0f, -1.0f, 1.0f,//
        -1.0f, 1.0f,  1.0f,//
        1.0f,  1.0f,  1.0f,//
        1.0f,  1.0f,  1.0f,//
        1.0f,  -1.0f, 1.0f,//
        -1.0f, -1.0f, 1.0f,//

        -1.0f, 1.0f,  -1.0f,//
        1.0f,  1.0f,  -1.0f,//
        1.0f,  1.0f,  1.0f, //
        1.0f,  1.0f,  1.0f, //
        -1.0f, 1.0f,  1.0f, //
        -1.0f, 1.0f,  -1.0f,//

        -1.0f, -1.0f, -1.0f,//
        -1.0f, -1.0f, 1.0f, //
        1.0f,  -1.0f, -1.0f,//
        1.0f,  -1.0f, -1.0f,//
        -1.0f, -1.0f, 1.0f, //
        1.0f,  -1.0f, 1.0f  //
    };
}

GLenum Skybox::deduceImageFormat()
{
    switch (mNrChannels)
    {
        case 1: return GL_RED;
        case 3: return GL_RGB;
        case 4: return GL_RGBA;
    }
}

void Skybox::loadTextureFace(const std::vector<std::string>& faces, unsigned faceId)
{
    unsigned char* mData = nullptr;
    mData = stbi_load(faces[faceId].c_str(), &mWidth, &mHeight, &mNrChannels, 0);
    auto format = deduceImageFormat();
    if (mData)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceId, 0, format, mWidth, mHeight, 0, format,
                     GL_UNSIGNED_BYTE, mData);
    }
    else
    {
        spdlog::error("Failed to load a texture: {}", faces[faceId]);
    }
    stbi_image_free(mData);
}