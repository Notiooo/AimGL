#pragma once
#include <Renderer/Graphics/3D/Model.h>
#include <World/Physics/Drawable/AABB.h>

class ColliderRegister;

/**
 * \brief Represents a button stand, an interactive object with clickable functionality.
 */
class ButtonStand
{
public:
    /**
     * \brief Initializes a Button Stand object with collision handling and position.
     * \param colliderRegister A register for managing scene collisions.
     * \param position The initial position of the Button Stand.
     */
    ButtonStand(ColliderRegister& colliderRegister, const glm::vec3& position);

    /**
     * \brief Draws the button stand on the given target with the specified camera perspective.
     * \param target The rendering target.
     * \param camera The camera used for rendering the sprite.
     */
    void draw(const Renderer& target, const Camera& camera) const;

    /**
     * Updates the Button Stand logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void update(const float& deltaTime);

    /**
     * \brief Registers a callback function to be called upon a button click event.
     * \param onShotFunction The function to execute when the button is clicked.
     */
    void onClick(std::function<void()> onShotFunction);

    /**
     * \brief It takes input (event) from the user and interprets it
     * \param event user input
     */
    void handleEvent(const sf::Event& event);

    /**
     * \brief Sets the position of the object.
     * \param newPosition The new position for the object.
     */
    void setPosition(const glm::vec3& newPosition);

private:
    /**
     * \brief Triggers the visual and audible indication of a button click.
     */
    void signalizeButtonClick();

private:
    Model mButtonStand;
    sf::SoundBuffer mSoundBuffer;
    sf::Sound mClickSound;
    ColliderRegister& mColliderRegister;
    AABB mCollisionBox;
    AABB mButtonShotTriggerBox;
    std::function<void()> mOnShotFunction = []()
    {
    };

    sf::Time mTimeOfClickAnimation = sf::seconds(1);
    sf::Clock mAnimationClock;
    bool isAnimationBeingPlayed = false;
    bool hasNewMouseClickOccured = true;
};
