#include "Texture.h"
#include "pch.h"

#include "Renderer3D/OpenglUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& filePath)
    : mTextureId(0)
    , mFilePath(filePath)
    , mData(nullptr)
    , mWidth(0)
    , mHeight(0)
    , mNrChannels(0)
{
    stbi_set_flip_vertically_on_load(true);
    mData = stbi_load(filePath.c_str(), &mWidth, &mHeight, &mNrChannels, 0);
    GLCall(glGenTextures(1, &mTextureId));
    GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    if (mData)
    {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA,
                            GL_UNSIGNED_BYTE, mData));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
        mAspectRatio = static_cast<float>(mWidth) / static_cast<float>(mHeight);
        unbind();
    }
    else
    {
        spdlog::error("Failed to load a texture: {}", filePath);
    }
    stbi_image_free(mData);
};

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &mTextureId));
}

void Texture::bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, mTextureId));
}

void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int Texture::width() const
{
    return mWidth;
}

int Texture::height() const
{
    return mHeight;
}

float Texture::aspectRatio() const
{
    return mAspectRatio;
}
