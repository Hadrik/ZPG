#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vertexColor;
out vec3 fragNormal;

void main()
{
    if (gl_VertexID > 36443) {
        vertexColor = vec3(0.f, 1.f, 0.f);
    } else {
        vertexColor = vec3(0.35f, 0.2f, 0.f);
    }

    fragNormal = normal;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}