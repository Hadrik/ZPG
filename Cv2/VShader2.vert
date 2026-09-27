#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

void main()
{
   vertexColor = color;
   gl_Position = vec4(0.2 * position + vec3(-0.3, -0.7, 0.0), 1.0);
}