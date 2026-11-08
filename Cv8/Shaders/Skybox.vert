#version 400

layout (location = 0) in vec3 position;

out vec3 direction;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    direction = position;
    gl_Position = (projectionMatrix * mat4(mat3(viewMatrix)) * vec4(position, 1.0)).xyww;
}
