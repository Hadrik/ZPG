//
// Created by trric on 25.10.2026.
//

#ifndef ZPG_POINTLIGHT_H
#define ZPG_POINTLIGHT_H

#include <glm/vec3.hpp>


class PointLight {
public:
    PointLight(const glm::vec3& position, const glm::vec3& color, float intensity)
        : _position(position), _color(color), _intensity(intensity) {}

    [[nodiscard]] const glm::vec3& getPosition() const { return _position; }
    [[nodiscard]] const glm::vec3& getColor() const { return _color; }
    [[nodiscard]] float getIntensity() const { return _intensity; }

private:
    glm::vec3 _position;
    glm::vec3 _color;
    float _intensity;
};



#endif //ZPG_POINTLIGHT_H
