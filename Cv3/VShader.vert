#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform float rotation = 0;
uniform float scale = 1;
uniform vec3 translation = vec3(0, 0, 0);

out vec3 vertexColor;

void main()
{
    vertexColor = abs(color);
    vec4 pos = vec4(cos(rotation) * position.x + sin(rotation) * position.z,
                    position.y,
                    -sin(rotation) * position.x + cos(rotation) * position.z,
                    1.0);
    pos.xyz *= scale;
    pos.xyz += translation;
    gl_Position = pos;
}