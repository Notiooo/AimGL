#pragma once
#include "ButtonStand.h"
#include "LongCrate.h"
#include "TargetManager.h"

#include <Renderer/Graphics/3D/Sprite3D.h>

/**
 * \brief Represents a SidewayMovingTargetsRange,
 * a shooting range featuring targets that move sideways.
 */
class SidewayMovingTargetsRange
{
public:
    /**
     * \brief Initializes a SidewayMovingTargetsRange object with collision
     * management and a specific position.
     * \param colliderRegister A register for managing collisions in the scene.
     * \param position The initial position of the SidewayMovingTargetsRange.
     */
    SidewayMovingTargetsRange(ColliderRegister& colliderRegister, const glm::vec3& position);

    /**
     * \brief Draws a shooting range to a given target
     * \param target The target to which the model is drawn
     * \param camera A camera in 3D space that looks at this object
     */
    void draw(const Renderer& target, const Camera& camera) const;

    /**
     * Updates the Shooting Range logic dependent, or independent of time, every rendered frame.
     * \param deltaTime the time that has passed since the game was last updated.
     */
    void update(const float& deltaTime);

    /**
     * \brief It takes input (event) from the user and interprets it
     * \param event user input
     */
    void handleEvent(const sf::Event& event);

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

private:
    /**
     * \brief Toggles the operational state of the sideway moving targets,
     * such as activating or deactivating them.
     */
    void toggleShootingRange();

private:
    constexpr static auto BOXES_DISTANCE = 6.f;
    ButtonStand mButtonStand;
    glm::vec3 mPosition;

    LongCrate mSmallerCrate;
    LongCrate mMediumCrate;
    LongCrate mLargeCrate;

    Texture mDirectionArrowTexture;
    Sprite3D mDirectionArrowPointingButton;

    Texture mTrainingLogoTexture;
    Sprite3D mTrainingLogo;

    TargetManager mTargetManager;
    bool mIsShootingRangeActive{false};
};
