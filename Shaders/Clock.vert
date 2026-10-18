#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float elapsedTime;

out vec3 vertexColor;
out vec3 fragNormal;

vec3 rotateHand(vec3 point, float angularSpeed) {
    float angle = -elapsedTime * angularSpeed;
    float sine = sin(angle);
    float cosine = cos(angle);
    vec2 offset = point.xy;
    return vec3(vec2(
        offset.x * cosine - point.y * sine,
        offset.x * sine + offset.y * cosine
    ), point.z);
}

void main()
{
    vertexColor = color;

    fragNormal = normal;
    vec3 animatedPosition = position;
    if (color == vec3(1.0, 0.0, 0.0)) {
        animatedPosition = rotateHand(position, 2.0 * 3.14159265 / 60.0);
    } else if (color == vec3(0.0, 1.0, 0.0)) {
        animatedPosition = rotateHand(position, 2.0 * 3.14159265 / 3600.0);
    } else if (color == vec3(0.0, 0.0, 1.0)) {
        animatedPosition = rotateHand(position, 2.0 * 3.14159265 / 43200.0);
    } else if (color == vec3(1.0, 1.0, 0.0)) {
        vertexColor = vec3(5.0, 195.0, 222.0) / 255.0;
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(animatedPosition, 1.0);
}