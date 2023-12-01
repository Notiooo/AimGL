#pragma once

/**
 * \brief Represents a 3D rotation using Euler angles.
 */
class Rotation3D
{
    glm::vec3 mRotation{0, 0, 0};

public:
    Rotation3D();
    Rotation3D(float yaw, float pitch, float roll);
    Rotation3D(const Rotation3D& rotation);
    Rotation3D& operator=(const Rotation3D& rotation);
    bool operator==(const Rotation3D&) const;
    Rotation3D operator+(const Rotation3D&) const;
    Rotation3D operator-(const Rotation3D&) const;
    Rotation3D operator*(const Rotation3D&) const;
    Rotation3D& operator+=(const Rotation3D&);
    Rotation3D& operator-=(const Rotation3D&);
    Rotation3D& operator*=(const Rotation3D&);
    friend Rotation3D operator*(const Rotation3D& lhs, float rhs);
    explicit operator glm::vec3();

    /**
     * \brief Angles of Euler rotation.
     */
    enum class EulerAngle
    {
        ROLL,
        PITCH,
        YAW
    };

    float& yaw = mRotation.x;
    float& pitch = mRotation.y;
    float& roll = mRotation.z;

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

private:
    explicit Rotation3D(const glm::vec3& rotation);
};


inline Rotation3D operator*(const Rotation3D& lhs, float rhs)
{
    return Rotation3D(lhs.mRotation * rhs);
}

inline Rotation3D operator*(float lhs, const Rotation3D& rhs)
{
    return rhs * lhs;
}