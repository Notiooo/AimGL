#include "Model.h"
#include "pch.h"

Model::Model(const std::string& objFilePath, const std::vector<TextureType>& texturesToLoad)
    : mShader{{ShaderType::VertexShader, "resources/Shaders/Graphics/Model/ModelTextured.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/Graphics/Model/ModelTextured.fs"}}
{
    ObjLoader objLoader(objFilePath, {ObjLoader::Flags::ForceCenterAtOrigin});
    // TODO: Storing texture this way is not the best idea as the texture
    // TODO: may be duplicated as many times as this object is loaded! :<<
    std::vector<Texture> textures;
    textures.reserve(textures.size());
    for (const auto& textureToLoad: texturesToLoad)
    {
        const auto& [texturePath, textureType] = textureToLoad;
        textures.emplace_back(texturePath, textureType);
    }
    mMesh = std::make_unique<Mesh>(std::move(objLoader.vertices()), std::move(objLoader.indices()),
                                   std::move(textures));
    mDimensions = objLoader.dimensions();
    setPosition({0, 0, 0});
}

Model::Model(const Model& rhs)
    : mShader(rhs.mShader.filePaths())
    , mMesh(std::make_unique<Mesh>(*rhs.mMesh))
    , mPosition(rhs.mPosition)
    , mRotationOrigin(rhs.mRotationOrigin)
    , mScale(rhs.mScale)
    , mRotation(rhs.mRotation)
    , mDimensions(rhs.mDimensions)
    , mLastCalculatedModel(rhs.mLastCalculatedModel)
{
    setPosition(mPosition);
}

Model& Model::operator=(const Model& rhs)
{
    // mShader = // TODO: Hmm it should be copied later on.
    mMesh = std::make_unique<Mesh>(*rhs.mMesh);// it completely copies new one
    mPosition = rhs.mPosition;
    mRotationOrigin = rhs.mRotationOrigin;
    mScale = rhs.mScale;
    mRotation = rhs.mRotation;
    mDimensions = rhs.mDimensions;
    mLastCalculatedModel = rhs.mLastCalculatedModel;
    setPosition(mPosition);
    return *this;
}

void Model::draw(const Renderer& target, const Camera& camera) const
{
    mShader.bind();
    mShader.setUniform("model", mLastCalculatedModel);
    mShader.unbind();
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
    updateModel();
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
    return mDimensions * mScale;
}

void Model::updateModel()
{
    mLastCalculatedModel = glm::mat4(1.0f);
    mLastCalculatedModel = glm::translate(mLastCalculatedModel, glm::vec3(mPosition));
    mLastCalculatedModel = glm::translate(mLastCalculatedModel, -mRotationOrigin);
    mLastCalculatedModel = mRotation.rotate(mLastCalculatedModel);
    mLastCalculatedModel = glm::translate(mLastCalculatedModel, mRotationOrigin);
    mLastCalculatedModel = glm::scale(mLastCalculatedModel, glm::vec3(mScale, mScale, mScale));
}