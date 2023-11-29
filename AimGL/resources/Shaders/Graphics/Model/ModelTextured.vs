#version 330 core

layout(location = 0) in vec3 position; // Vertex position
layout(location = 1) in vec3 normal; // Norm
layout(location = 2) in vec2 texCoords; // Texture coordinates

out vec3 FragmentNormal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model = mat4(1.0);
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = texCoords;
    mat4 mvp = projection * view * model;
    FragPos = vec3(model * vec4(normal, 1.0));
    FragmentNormal = mat3(transpose(inverse(model))) * normal;

    gl_Position = mvp * vec4(position, 1.0);
}