//
// Created by trric on 25.10.2026.
//

#ifndef ZPG_POINTLIGHT_H
#define ZPG_POINTLIGHT_H

#include <glm/vec3.hpp>


class PointLight {
public:
    PointLight(const glm::vec3& color, const float intensity)
        : _color(color), _intensity(intensity) {}

    [[nodiscard]] Transformation& transformation() { return _transform; }
    [[nodiscard]] glm::vec3 getPosition() const { return _transform.getPosition(); }
    [[nodiscard]] const glm::vec3& getColor() const { return _color; }
    [[nodiscard]] float getIntensity() const { return _intensity; }
    [[nodiscard]] float getConstant() const { return _constant; }
    [[nodiscard]] float getLinear() const { return _linear; }
    [[nodiscard]] float getQuadratic() const { return _quadratic; }

private:
    Transformation _transform;
    glm::vec3 _color;
    float _intensity;
    float _constant = 1.0f;
    float _linear = 0.09f;
    float _quadratic = 0.032f;
};



#endif //ZPG_POINTLIGHT_H
