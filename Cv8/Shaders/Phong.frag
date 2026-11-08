#version 400

in vec3 worldNorm;
in vec3 worldPos;
in vec3 vertColor;
in vec2 uv;

uniform bool hasColor;
uniform bool hasUv;
uniform mat4 viewMatrix;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform float lightConstant;
uniform float lightLinear;
uniform float lightQuadratic;
uniform sampler2D textureUnit;

out vec4 FragColor;

float attenuation(float d, float c, float l, float q) {
    float att = 1.0 / (c + l * d + q * d * d);
    return clamp(att, 0.0, 1.0);
}

void main() {
    vec3 color = hasUv ? texture(textureUnit, uv).rgb : vertColor;

    // Ambient
    float ambientStrength = 0.01;
    vec3 ambient = vec3(1.0, 1.0, 1.0) * ambientStrength;

    // Diffuse
    vec3 norm = normalize(worldNorm);
    float lightDistance = length(lightPosition - worldPos);
    float att = attenuation(lightDistance, lightConstant, lightLinear, lightQuadratic);
    vec3 lightDir = normalize(lightPosition - worldPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * color * lightIntensity * att;

    // Specular
    float specularStrength = 1.0;
    if (dot(norm, lightDir) < 0.0) {
        specularStrength = 0.0;
    }
    vec3 viewDir = normalize(cameraPosition - worldPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    float specular = specularStrength * spec * lightIntensity * att;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}