#version 330 core

layout(location = 0) in vec3 position; // Vertex position
layout(location = 1) in vec2 texCoords; // Texture coordinates

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = texCoords;
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(position, 1.0);
}