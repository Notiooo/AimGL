#pragma once
#include <Renderer/Graphics/3D/Model.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Renderer;
class Camera;

/**
 * \brief Weapons the player can shoot with.
 */
class Rifle
{
public:
    /**
     * \brief Constructor of Rifle class
     * \param camera The camera to which the weapon should be attached
     */
    explicit Rifle(Camera& camera);

    /**
     * \brief Draws a Rifle to a given target
     * \param target The target to which the sprite is drawn
     */
    void draw(const Renderer& target) const;

    /**
     * Updates the Rifle logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void update(const float& deltaTime);

    /**
     * \brief It takes input (event) from the user and interprets it
     * \param event user input
     */
    void handleEvent(const sf::Event& event);

private:
    /**
     * \brief Updates logic related to attaching rifle to camera
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void updateAttachToCamera(const float& deltaTime);

private:
    Model mGun;
    Camera& mCamera;
    static constexpr auto RECOIL_OFFSET_INCREMENT = 0.2f;
    static constexpr auto RECOIL_OFFSET_MAX = 0.3f;
    float mCurrentRecoil{0};
    sf::SoundBuffer mSoundBuffer;
    sf::Sound mGunShotSound;
};