#version 330 core
out vec4 FragColor;

uniform vec3 aabbColor = vec3(0,0.8,0);

void main() {
    FragColor = vec4(aabbColor, 1.0);
}
