#include "Rotation3D.h"
#include "pch.h"

Rotation3D::Rotation3D()
    : mRotation(0, 0, 0)
{
}

Rotation3D::Rotation3D(float yaw, float pitch, float roll)
    : mRotation(yaw, pitch, roll)
{
}

Rotation3D::Rotation3D(const Rotation3D& rotation)
    : mRotation(rotation.mRotation)
{
}

Rotation3D& Rotation3D::operator=(const Rotation3D& rotation)
{
    mRotation = rotation.mRotation;
    return *this;
}

glm::mat4 Rotation3D::rotate(glm::mat4 model, std::initializer_list<EulerAngle> ordering) const
{
    for (const auto axisRotation: ordering)
    {
        switch (axisRotation)
        {
            case EulerAngle::YAW:
                model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
                break;
            case EulerAngle::PITCH:
                model = glm::rotate(model, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
                break;
            case EulerAngle::ROLL:
                model = glm::rotate(model, glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
                break;
        }
    }
    return model;
}

void Rotation3D::imGuiRotationSlider()
{
    ImGui::SliderFloat("Roll", &roll, -360, 360.0f);
    ImGui::SliderFloat("Pitch", &pitch, -360, 360.0f);
    ImGui::SliderFloat("Yaw", &yaw, -360, 360.0f);
}

bool Rotation3D::operator==(const Rotation3D& rhs) const
{
    return mRotation == rhs.mRotation;
}

Rotation3D Rotation3D::operator+(const Rotation3D& rhs) const
{
    return Rotation3D(mRotation + rhs.mRotation);
}

Rotation3D Rotation3D::operator-(const Rotation3D& rhs) const
{
    return Rotation3D(mRotation - rhs.mRotation);
}

Rotation3D Rotation3D::operator*(const Rotation3D& rhs) const
{
    return Rotation3D(mRotation * rhs.mRotation);
}

Rotation3D& Rotation3D::operator+=(const Rotation3D& rhs)
{
    mRotation += rhs.mRotation;
    return *this;
}

Rotation3D& Rotation3D::operator-=(const Rotation3D& rhs)
{
    mRotation -= rhs.mRotation;
    return *this;
}

Rotation3D& Rotation3D::operator*=(const Rotation3D& rhs)
{
    mRotation *= rhs.mRotation;
    return *this;
}

Rotation3D::operator glm::vec<3, float>() const
{
    return mRotation;
}

Rotation3D::Rotation3D(const glm::vec3& rotation)
    : mRotation(rotation)
{
}
