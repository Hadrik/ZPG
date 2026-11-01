#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normCol;
layout (location = 2) in vec3 cNormal;

uniform bool hasColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldNorm;
out vec3 worldPos;
out vec3 vertColor;

void main() {
    vec3 normal = hasColor ? cNormal : normCol;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
    worldPos = vec3(modelMatrix * vec4(position, 1.0));

    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

    worldNorm = normalMatrix * normal;
//    worldNorm = mat3(modelMatrix) * normal;
//    worldNorm = normal;

    vertColor = hasColor ? normCol : vec3(0.385, 0.647, 0.812);
}