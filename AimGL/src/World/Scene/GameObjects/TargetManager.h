#pragma once
#include "Renderer/Graphics/3D/Model.h"
#include "World/Physics/Drawable/AABB.h"
#include "World/Scene/GameObjects/Target.h"

#include <deque>

class ColliderRegister;


/**
 * \brief Manages the creation, movement, and removal of targets in a shooting range.
 */
class TargetManager
{
public:
    TargetManager(ColliderRegister& colliderRegister, const glm::vec3& position,
                  const sf::Time& timeToSpawn, const sf::Time& timeToDisappear);

    /**
     * \brief Draws a Targets for a given target
     * \param rendererTarget The target to which the models are drawn
     * \param camera A camera in 3D space that looks at this object
     */
    void draw(const Renderer& rendererTarget, const Camera& camera) const;

    /**
     * Updates the TargetSpawner logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void update(const float& deltaTime);

    /**
     * \brief Starts the target management process.
     */
    void start();

    /**
     * \brief Stops the target management process.
     */
    void stop();

    /**
     * \brief Sets the base position for spawning new targets.
     * \param newPosition The new base position.
     */
    void setPosition(const glm::vec3& newPosition);

    /**
     * \brief Sets the range within which targets can spawn.
     * \param minPadding The minimum offset from the base position.
     * \param maxPadding The maximum offset from the base position.
     */
    void setSpawnRange(const glm::vec3& minPadding, const glm::vec3& maxPadding);

    /**
     * \brief Sets the movement parameters for the targets.
     * \param direction The direction of movement.
     * \param speed The speed of movement.
     */
    void setTargetMovement(const glm::vec3& direction, float speed);

private:
    struct SpawnedTarget
    {
        Target target;
        sf::Clock timeSinceSpawn;
    };

    /**
     * \brief Generates a new random position offset for target spawning.
     * \return The generated random offset position.
     */
    glm::vec3 generateNewRandomOffset() const;

    /**
     * \brief Removes targets that have been shot.
     */
    void removeShotTargets();

    /**
     * \brief Determines if a new target should be spawned.
     * \return True if a new target should be spawned, false otherwise.
     */
    bool shouldNewTargetBeSpawn() const;

    /**
     * \brief Determines if an existing target should be removed.
     * \return True if an old target should be removed, false otherwise.
     */
    bool shouldOldTargetBeRemoved() const;

    /**
     * \brief Spawns a new target.
     */
    void spawnNewTarget();

    /**
     * \brief Removes an old target.
     */
    void removeOldTarget();

private:
    std::list<SpawnedTarget> mTargetsWithSpawntime;
    sf::SoundBuffer mBuffer;
    sf::Sound mSound;
    Model mSpherePrefab;

    ColliderRegister& mColliderRegister;
    glm::vec3 mPosition;
    sf::Time mTimeToSpawn;
    sf::Clock mNextSpawnClock;
    sf::Time mTimeToDisappear;
    bool mIsManagerActive{false};

    glm::vec3 mMinPadding{-1, -1, 0};
    glm::vec3 mMaxPadding{1, 1, 0};

    glm::vec3 mTargetsDirection = {0, 0, 0};
    float mTargetsSpeed = 0;
};
