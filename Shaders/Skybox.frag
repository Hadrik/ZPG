#version 400

in vec3 direction;

uniform samplerCube skybox;

out vec4 FragColor;

void main() {
    FragColor = texture(skybox, direction);
}
