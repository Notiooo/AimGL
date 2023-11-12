#pragma once

/**
 * \brief The image, closed in a buffer, lives on the graphics card.
 */
class Texture
{
public:
    /**
     * \brief Creates a texture based on the file path to image
     * \param filePath Path to the image
     */
    Texture(const std::string& filePath);

    /**
     * \brief Removes texture
     */
    ~Texture();

    /**
     * \brief Binds a texture for rendering
     * \param slot Slot to which the texture will be binded (can be obtained from the shader level)
     */
    void bind(unsigned int slot = 0) const;

    /**
     * \brief Unbinds the texture from rendering
     */
    void unbind() const;

    /**
     * \brief Returns the width of the texture
     * \return Width of the texture
     */
    int width() const;

    /**
     * \brief Returns the height of the texture
     * \return Height of the texture
     */
    int height() const;

    /**
     * \brief Returns the aspect ratio of the image
     * \return Aspect ratio of the image
     */
    float aspectRatio() const;

private:
    unsigned int mTextureId;
    std::string mFilePath;
    unsigned char* mData;
    float mAspectRatio;
    int mWidth, mHeight, mNrChannels;
};