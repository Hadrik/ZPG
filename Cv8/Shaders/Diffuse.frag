#version 400

in vec3 worldNorm;
in vec3 worldPos;
in vec3 vertColor;

uniform bool hasColor;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 FragColor;

void main() {
    vec3 lightDirection = normalize(lightPosition - worldPos);
    float diff = max(dot(lightDirection, normalize(worldNorm)), 0.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 0.1);
    vec4 color = vec4(hasColor ? vertColor : vec3(0.385, 0.647, 0.812), 1.0);
    FragColor = ambient + (diff * color);
}
