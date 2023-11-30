#pragma once

/**
 * \brief Represents a 3D rotation using Euler angles.
 */
struct Rotation3D
{
    /**
     * \brief Angles of Euler rotation.
     */
    enum class EulerAngle
    {
        ROLL,
        PITCH,
        YAW
    };

    float yaw{0};
    float pitch{0};
    float roll{0};

    /**
     * \brief Applies rotation to a 3D model matrix in a specified order.
     * \param model The model matrix to be rotated.
     * \param ordering The order in which yaw, pitch, and roll are applied.
     * \return The rotated model matrix.
     */
    [[nodiscard]] glm::mat4 rotate(glm::mat4 model,
                                   std::initializer_list<EulerAngle> ordering = {
                                       EulerAngle::YAW, EulerAngle::PITCH, EulerAngle::ROLL}) const;

    /**
     * \brief Renders an ImGui slider interface for adjusting the rotation.
     */
    void imGuiRotationSlider();
};
