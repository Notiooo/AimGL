#version 330 core

out vec4 FragColor;

uniform vec4 color = vec4(1,0,0, 1.f);

void main()
{
    FragColor = color;
    if(FragColor.a == 0.0)
		discard;
}