#version 330 core
out vec4 FragColor;

uniform vec3 rayColor = vec3(0,1,0);

void main() {
    FragColor = vec4(rayColor, 1.0);
}
