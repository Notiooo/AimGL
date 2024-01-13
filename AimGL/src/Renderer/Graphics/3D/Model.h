#pragma once
#include "Core/Mesh.h"
#include "Utils/Rotation3D.h"

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
    Model(const Model& rhs);
    Model& operator=(const Model& rhs);

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

    /**
     * \brief Scales the model uniformly.
     * \param scale The uniform scale factor.
     */
    void setScale(float scale);

    /**
     * \brief Retrieves the current rotation of the object.
     * \return The object's rotation as a Rotation3D instance.
     */
    Rotation3D rotation() const;

    /**
     * \brief Sets the object's rotation.
     * \param rotation The new rotation that the object should take
     */
    void setRotation(const Rotation3D& rotation);

    /**
     * \brief Resets the model's rotation origin to its default position (0,0,0).
     */
    void resetRotationOrigin();

    /**
     * \brief Sets the model's rotation origin.
     * \param vec The 3D vector defining the new rotation origin.
     */
    void setRotationOrigin(const glm::vec3& vec);

    /**
     * \brief Gets the model's current position.
     * \return The 3D position vector of the model.
     */
    glm::vec3 position() const;

    /**
     * \brief Gets the model's dimensions.
     * \return The 3D vector representing the model's dimensions.
     */
    glm::vec3 dimensions() const;

    /**
     * \brief Displays a debug ImGui window that allows to change the internal
     * variables of the 3d model.
     * \param name Optional name of the model (it can be seen in the window name).
     */
    void showDebugImGui(std::string name = "");

    /**
     * \brief Get a modifiable reference to the entity's mesh.
     * \return Mesh reference.
     */
    Mesh& mesh();

    /**
     * \brief Get a read-only reference to the entity's mesh.
     * \return Constant Mesh reference.
     */
    const Mesh& mesh() const;

private:
    /**
     * \brief Updates the model in the shader
     */
    void updateModel();

private:
    Shader mShader;
    std::unique_ptr<Mesh> mMesh;
    glm::vec3 mPosition{0, 0, 0};
    glm::vec3 mRotationOrigin{0, 0, 0};
    float mScale{1};
    Rotation3D mRotation;
    glm::vec3 mDimensions{};
    glm::mat4 mLastCalculatedModel{};
};