#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D spriteTexture;
uniform float opacity = 0.f;

void main()
{
    color = texture(spriteTexture, TexCoords);
    color.a = min(color.a, opacity);
    if(color.a == 0.0)
		discard;
}