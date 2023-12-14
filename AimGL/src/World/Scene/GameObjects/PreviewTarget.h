#pragma once
#include "Renderer/Graphics/3D/Model.h"
#include "World/Physics/Drawable/AABB.h"

class ColliderRegister;

/**
 * \brief Target possible to shoot down with weapon.
 *
 * @warning This facility is for illustrative purposes only.
 * It will be removed from here. It is not intended for use in the final game
 */
class PreviewTarget
{
public:
    PreviewTarget(ColliderRegister& colliderRegister, const glm::vec3& position);

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

private:
    AABB mAABB;
    Model mSphere;
    glm::vec3 mPosition;
    sf::SoundBuffer mBuffer;
    sf::Sound mSound;
    bool mIsAboutToBeDeleted = false;
};
