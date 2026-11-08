#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 uvCoord;

uniform bool hasColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldNorm;
out vec3 worldPos;
out vec3 vertColor;
out vec2 uv;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
    worldPos = vec3(modelMatrix * vec4(position, 1.0));

    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNorm = normalMatrix * normal;

    vertColor = color;
    uv = uvCoord;
}