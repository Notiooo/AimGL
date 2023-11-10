#version 330 core

layout(location = 0) in vec2 position; // Vertex position
layout(location = 1) in vec2 texCoords; // Texture coordinates

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection = mat4(1.0); // For 2D it is identity
uniform mat4 windowOrthoProjection;

void main()
{
    TexCoords = texCoords;
    mat4 mvp = windowOrthoProjection * model;
    gl_Position = mvp * vec4(position, 0.0, 1.0);
}