#include "Mesh.h"
#include "pch.h"

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned>&& indices,
           std::vector<Texture>&& textures)
    : vertices(std::move(vertices))
    , indices(std::move(indices))
    , textures(std::move(textures))
{
    mVBO.setBuffer(this->vertices);
    mEBO.setBuffer(this->indices);

    mVAO.bind();
    mVBO.bind();
    mBufferLayout.push<float>(3);
    mBufferLayout.push<float>(3);
    mBufferLayout.push<float>(2);
    mVAO.setBuffer(mVBO, mBufferLayout);
    mVAO.unbind();
}

void Mesh::setTextureToShaderUniform(const Shader& shader, const Texture& texture) const
{
    switch (texture.type())
    {
        case Texture::Type::Diffuse:
            shader.setUniform("material.diffuse", 0);
            shader.setUniform("material.isDiffusePresent", true);
            break;
        case Texture::Type::Specular:
            shader.setUniform("material.specular", 1);
            shader.setUniform("material.isSpecularPresent", true);
            break;
        default:
            spdlog::warn(
                "Trying to draw texture of unsupported type inside Mesh. TextureType used: {}",
                toString(texture.type()));
    }
}

void Mesh::setDefaultValuesToMaterialUniforms(const Shader& shader) const
{
    shader.setUniform("material.isDiffusePresent", false);
    shader.setUniform("material.isSpecularPresent", false);
}

void Mesh::draw(const Renderer& target, const Camera& camera, const Shader& shader) const
{
    shader.bind();
    setDefaultValuesToMaterialUniforms(shader);
    for (auto i = 0; i < textures.size(); ++i)
    {
        auto& texture = textures[i];
        setTextureToShaderUniform(shader, texture);
        texture.bind(i);
    }
    target.draw3D(mVAO, mEBO, shader, camera);
}

void Mesh::setTexture(Texture&& newTexture)
{
    auto it = std::find_if(textures.begin(), textures.end(),
                           [&newTexture](const auto& texture)
                           {
                               return texture.type() == newTexture.type();
                           });

    if (it != textures.end())
    {
        *it = std::move(newTexture);
    }

    textures.push_back(std::move(newTexture));
}
