#include "LongCrate.h"
#include "pch.h"

LongCrate::LongCrate(ColliderRegister& colliderRegister, const glm::vec3& position)
    : mLongCrate("resources/Models/long-crate/long-crate.obj",
                 {{"resources/Models/long-crate/diffuse.png", Texture::Type::Diffuse},
                  {"resources/Models/long-crate/specular.png", Texture::Type::Specular}})
    , mPosition(position)
    , mAABB(colliderRegister, {0, 0, 0}, mLongCrate.dimensions())
{
    mAABB.colliderTag(ColliderTag::Solid);
    setPosition(mPosition);
}

void LongCrate::draw(const Renderer& target, const Camera& camera) const
{
    mLongCrate.draw(target, camera);
    mAABB.draw(target, camera);
}

void LongCrate::showDebugImGui(std::string name)
{
    name = "[Model] " + name;
    ImGui::Begin(name.c_str());
    ImGui::SliderFloat3("Position", &mPosition[0], -50, 50.f);
    mRotation.imGuiRotationSlider();
    ImGui::End();
    setPosition(mPosition);
    setRotation(mRotation);
}

void LongCrate::setPosition(const glm::vec3& newPosition)
{
    mLongCrate.setPosition(newPosition);
    mAABB.setPosition(mLongCrate.position() - mLongCrate.dimensions() / 2.f);
}

void LongCrate::setScale(float scaleRatio)
{
    mLongCrate.setScale(scaleRatio);
    mAABB.setScale(scaleRatio);
}

void LongCrate::setRotation(const Rotation3D& rotation)
{
    mLongCrate.setRotation(rotation);
    mAABB.setRotation(rotation);
}
