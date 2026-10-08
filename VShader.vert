#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
//layout (location = 2) in vec3 normal;

uniform vec4 modelMatrix;

out vec3 vertexColor;

void main()
{
    vertexColor = abs(color);
    gl_Position = modelMatrix * vec4(position, 1.0);
}