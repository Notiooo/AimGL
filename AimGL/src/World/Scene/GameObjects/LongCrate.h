#pragma once
#include <Renderer/Graphics/3D/Model.h>
#include <World/Physics/Drawable/AABB.h>

class Camera;
class Renderer;
class ColliderRegister;

/**
 * \brief Represents a LongCrate, an crate object used in the scene.
 */
class LongCrate
{
public:
    /**
     * \brief Initializes a LongCrate object with collision handling and a specific position.
     * \param colliderRegister A register for managing scene collisions.
     * \param position The initial position of the LongCrate in the scene.
     */
    LongCrate(ColliderRegister& colliderRegister, const glm::vec3& position);

    /**
     * \brief Draws a long crate to a given target
     * \param target The target to which the model is drawn
     * \param camera A camera in 3D space that looks at this object
     */
    void draw(const Renderer& target, const Camera& camera) const;

    /**
     * \brief Displays a debug ImGui window that allows to change the internal
     * variables of the 3d model.
     * \param name Optional name of the model (it can be seen in the window name).
     */
    void showDebugImGui(std::string name = "");

    /**
     * \brief Sets the position of the object.
     * \param newPosition The new position for the object.
     */
    void setPosition(const glm::vec3& newPosition);

    /**
     * \brief Sets the scale of the object.
     * \param scaleRatio The factor by which to scale the object.
     */
    void setScale(float scaleRatio);

    /**
     * \brief Sets the rotation of the object.
     * \param rotation The new rotation parameters for the object.
     */
    void setRotation(const Rotation3D& rotation);

private:
    Model mLongCrate;
    glm::vec3 mPosition;
    Rotation3D mRotation{0, 0, 0};
    AABB mAABB;
};
