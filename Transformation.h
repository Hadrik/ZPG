//
// Created by trric on 04.10.2026.
//

#ifndef ZPG_TRANSFORMATION_H
#define ZPG_TRANSFORMATION_H
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"


class Transformation {
public:
    Transformation() = default;
    ~Transformation() = default;

    Transformation& translate(glm::vec3 translation);
    Transformation& scale(glm::vec3 scale);
    Transformation& scale(float scale);
    Transformation& rotate(float angle, glm::vec3 axis);

    [[nodiscard]] const glm::mat4& getMatrix() const { return _matrix; }

private:
    glm::mat4 _matrix = glm::mat4(1.0f);
};



#endif //ZPG_TRANSFORMATION_H
