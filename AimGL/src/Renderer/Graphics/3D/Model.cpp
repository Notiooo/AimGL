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
        case Origin::LeftBottom: mPosition += mObjLoader.dimensions() / 2.f; break;
        case Origin::CenterBottom: mPosition.y += mObjLoader.dimensions().y / 2.f; break;
    }
    updateModel();
}

void Model::updateModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mPosition));
    // TODO: Add rotation and scale to the model
    // model = glm::rotate(model, glm::radians(mRotation.first), mRotation.second);
    // model = glm::scale(model, glm::vec3(mDimensionsNormalized * mScale / 2.f, 1.0f));
    mShader.bind();
    mShader.setUniform("model", model);
    mShader.unbind();
}
