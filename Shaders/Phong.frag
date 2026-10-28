#version 400

in vec3 worldNorm;
in vec3 worldPos;
in vec3 vertColor;

uniform bool hasColor;
uniform mat4 viewMatrix;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(worldNorm);
    vec3 lightDir = normalize(lightPosition - worldPos);
    vec3 viewDir = normalize(cameraPosition - worldPos);

    float diff = max(dot(lightDir, norm), 0.0);

    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec4 ambient = vec4(hasColor ? vertColor * 0.1 : vec3(0.1, 0.1, 0.1), 1.0);
    vec4 color = vec4(hasColor ? vertColor : vec3(0.385, 0.647, 0.812), 1.0);

    FragColor = ambient + (diff * color) + (spec);
}