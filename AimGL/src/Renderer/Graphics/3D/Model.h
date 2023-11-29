#pragma once
#include "Core/Mesh.h"

#include <Renderer/Renderer.h>
#include <Resources/ObjLoader.h>

/**
 * \brief Texture along with the type of texture it represents
 */
struct TextureType
{
    std::string texturePath;
    Texture::Type textureType;
};

/**
 * \brief A class representing a 3D model in the game's 3D space
 */
class Model
{
public:
    /**
     * \brief Model class constructor
     * \param objFilePath Path to a file with the extension .obj, which is a
     * representation of a 3d model
     * \param textures Path to the texture files and types that should be applied to the object.
     */
    explicit Model(const std::string& objFilePath, const std::vector<TextureType>& textures = {});

    /**
     * \brief Determines the point at which the model has its position (0,0,0)
     */
    enum class Origin
    {
        LeftBottom,
        Center,
        CenterBottom
    };

    /**
     * \brief Draws a model for a given target
     * \param target The target to which the model is drawn
     * \param camera A camera in 3D space that looks at this object
     */
    void draw(const Renderer& target, const Camera& camera) const;

    /**
     * \brief Sets new 3d model position in space
     * \param newPosition New 3d model position in space
     * \param origin Point at which the model has its position (0,0,0)
     */
    void setPosition(const glm::vec3& newPosition, Origin origin = Origin::CenterBottom);

private:
    /**
     * \brief Updates the model in the shader
     */
    void updateModel();

private:
    Shader mShader;
    ObjLoader mObjLoader;
    std::unique_ptr<Mesh> mMesh;
    glm::vec3 mPosition{0, 0, 0};
};
