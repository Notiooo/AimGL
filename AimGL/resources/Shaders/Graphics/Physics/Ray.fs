#version 330 core
out vec4 FragColor;

uniform vec3 rayColor = vec3(0,0.8,0);

void main() {
    FragColor = vec4(rayColor, 1.0);
}
