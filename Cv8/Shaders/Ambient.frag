#version 400

in vec3 worldNorm;
in vec3 worldPos;
in vec3 vertColor;

uniform bool hasColor;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 FragColor;

void main() {
    FragColor = vec4(hasColor ? vertColor : vec3(0.1, 0.1, 0.1), 1.0);
}
