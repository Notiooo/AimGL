#pragma once
#include "Renderer/Graphics/3D/Model.h"
#include "World/Physics/Drawable/AABB.h"

class ColliderRegister;

/**
 * \brief Target possible to shoot down with weapon.
 */
class Target
{
public:
    Target(ColliderRegister& colliderRegister, const glm::vec3& position);
    Target(ColliderRegister& colliderRegister, const glm::vec3& position, Model model);
    Target(const Target& rhs);

    /**
     * \brief Draws a PreviewTarget for a given target
     * \param target The target to which the model is drawn
     * \param camera A camera in 3D space that looks at this object
     */
    void draw(const Renderer& target, const Camera& camera) const;

    /**
     * Updates the PreviewTarget logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void update(const float& deltaTime);

    /**
     * \brief Checks if the target has been shot.
     * \return True if the target has been shot, false otherwise.
     */
    bool hasBeenShot() const;

    /**
     * \brief Sets the movement parameters for the target.
     * \param direction The direction of movement.
     * \param speed The speed of the movement.
     */
    void setMovement(const glm::vec3& direction, float speed);

private:
    /**
     * \brief Prepares the target by positioning it at the specified location, and setting callback
     * \param position The position where the target is to be placed.
     */
    void prepareTarget(const glm::vec3& position);

private:
    Model mSphere;
    AABB mAABB;
    glm::vec3 mPosition{};
    bool mHasBeenShot = false;
    float mSpeed = 0;
    glm::vec3 mDirectionMovement = {0, 0, 0};
};
