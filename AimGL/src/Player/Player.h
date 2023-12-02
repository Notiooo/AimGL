#pragma once
#include <Renderer/Graphics/2D/Sprite2D.h>
#include <World/Camera.h>
#include <World/Scene/GameObjects/Rifle.h>

class Renderer;
class Camera;

namespace sf
{
class Event;
}

/**
 * \brief The class that defines the player (physics, camera and all things related to the player)
 */
class Player
{
public:
    /**
     * \brief Player class constructor
     * \param window The window into which the player's eye view is rendered
     */
    explicit Player(WindowToRender& window);

    static constexpr auto PLAYER_HEGIHT = 0.8f;
    static constexpr auto PLAYER_MAX_HORIZONTAL_SPEED = 5.f;
    static constexpr auto PLAYER_WALKING_DECELERATE_RATIO = 10.f;
    static constexpr auto PLAYER_JUMP_FORCE = 0.04f;
    static constexpr auto PLAYER_WALKING_SPEED = 2.5f;
    static constexpr auto PLAYER_MAX_FALLING_SPEED = 8.f;

    /**
     * \brief Draws all player components to a given target
     * \param target The target to which the model is drawn
     */
    void draw(const Renderer& target) const;

    /**
     * Updates the Player logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void update(const float& deltaTime);

    /**
     * \brief Updates the Player logic at equal intervals independent of the frame rate.
     * \param deltaTime Time interval
     */
    void fixedUpdate(const float& deltaTime);

    /**
     * @brief Handles keyboard states such as button presses and responds accordingly
     * @param deltaTime the time that has passed since the game was last updated.
     */
    void handleMovementKeyboardInputs(const float& deltaTime);

    /**
     * \brief The player will try to jump if the player is on the ground
     */
    void tryJump();

    /**
     * \brief It takes input (event) from the user and interprets it
     * \param event user input
     */
    void handleEvent(const sf::Event& event);

    /**
     * @brief Enables/disables player controls.
     */
    void toggleControls();

    /**
     * \brief Returns the player's camera
     * \return Player's camera
     */
    Camera& camera();

    /**
     * \brief Returns the player's camera
     * \return Player's camera
     */
    const Camera& camera() const;

private:
    /**
     * \brief Updates the player's physics
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void updatePhysics(float deltaTime);

    /**
     * \brief Reduces the player's velocity by gradually decelerating it
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void decelerateVelocity(const float& deltaTime);

    /**
     * \brief Controls the player's vertical position by applying gravity, for example
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void manageVerticalVelocity(const float& deltaTime);

    /**
     * \brief Limits player's speed to maximum level
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void limitVelocity(const float& deltaTime);

    /**
     * \brief Checks if the player is on the ground
     * \return True if the player is on the ground, false otherwise
     */
    bool isOnGround() const;

    /**
     * \brief Manages walking sound effects based on the player's movement.
     * \param playerWalkingVector glm::vec3 indicating the direction of player movement.
     *  A zero vector suggests no movement, while a non-zero vector indicates movement.
     */
    void manageWalkingSounds(const glm::vec3& playerWalkingVector);

private:
    Camera mCamera;
    glm::vec3 mPosition{0, 0, 0};
    glm::vec3 mVelocity{0, 0, 0};
    Rifle mRifle;
    Texture mCrosshairTexture;
    Sprite2D mCrosshair;
    sf::SoundBuffer mSoundBuffer;
    sf::Sound mWalkingSound;
};