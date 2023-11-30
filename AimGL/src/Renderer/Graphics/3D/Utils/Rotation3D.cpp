#include "Rotation3D.h"
#include "pch.h"

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
