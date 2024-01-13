#include "Model.h"
#include "pch.h"

Model::Model(const std::string& objFilePath, const std::vector<TextureType>& texturesToLoad)
    : mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Model/ModelTextured.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Model/ModelTextured.fs"}}
    , mObjLoader(objFilePath, {ObjLoader::Flags::ForceCenterAtOrigin})
{
    // TODO: Storing texture this way is not the best idea as the texture
    // TODO: may be duplicated as many times as this object is loaded! :<<
    std::vector<Texture> textures;
    textures.reserve(textures.size());
    for (const auto& textureToLoad: texturesToLoad)
    {
        const auto& [texturePath, textureType] = textureToLoad;
        textures.emplace_back(texturePath, textureType);
    }
    mMesh = std::make_unique<Mesh>(std::move(mObjLoader.vertices()),
                                   std::move(mObjLoader.indices()), std::move(textures));
    setPosition({0, 0, 0});
}

void Model::draw(const Renderer& target, const Camera& camera) const
{
    mMesh->draw(target, camera, mShader);
}

void Model::setPosition(const glm::vec3& newPosition, Origin origin)
{
    mPosition = newPosition;
    switch (origin)
    {
        case Origin::Center: break;
        case Origin::LeftBottom: mPosition += dimensions() / 2.f; break;
        case Origin::CenterBottom: mPosition.y += dimensions().y / 2.f; break;
    }
    updateModel();
}

void Model::setScale(float scale)
{
    mScale = scale;
    updateModel();
}

Rotation3D Model::rotation() const
{
    return mRotation;
}

void Model::setRotation(const Rotation3D& rotation)
{
    mRotation = rotation;
}

void Model::resetRotationOrigin()
{
    mRotationOrigin = {0, 0, 0};
}

void Model::setRotationOrigin(const glm::vec3& vec)
{
    mRotationOrigin = vec;
}

void Model::showDebugImGui(std::string name)
{
    name = "[Model] " + name;
    ImGui::Begin(name.c_str());
    ImGui::SliderFloat3("Position", &mPosition[0], -50, 50.f);
    mRotation.imGuiRotationSlider();
    ImGui::SliderFloat("Scale", &mScale, 0, 4.0f);
    ImGui::End();
    updateModel();
}

Mesh& Model::mesh()
{
    return *mMesh;
}

const Mesh& Model::mesh() const
{
    return *mMesh;
}

glm::vec3 Model::position() const
{
    return mPosition;
}

glm::vec3 Model::dimensions() const
{
    return mObjLoader.dimensions() * mScale;
}

void Model::updateModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mPosition));
    model = glm::translate(model, -mRotationOrigin);
    model = mRotation.rotate(model);
    model = glm::translate(model, mRotationOrigin);
    model = glm::scale(model, glm::vec3(mScale, mScale, mScale));

    mShader.bind();
    mShader.setUniform("model", model);
    mShader.unbind();
}
