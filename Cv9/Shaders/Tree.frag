#version 330 core

in vec3 vertexColor;
in vec3 fragNormal;

out vec4 FragColor;

void main()
{
    float shade = 0.3 + 0.7 * abs(fragNormal.y);
    FragColor = vec4(shade * vertexColor, 1.0);
}