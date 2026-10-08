//
// Created by trric on 04.10.2026.
//

#include "Transformation.h"

#include "glm/ext/matrix_transform.hpp"

Transformation& Transformation::translate(const glm::vec3 translation) {
    _matrix = glm::translate(_matrix, translation);
    return *this;
}

Transformation& Transformation::scale(const glm::vec3 scale) {
    _matrix = glm::scale(_matrix, scale);
    return *this;
}

Transformation& Transformation::scale(const float scale) {
    _matrix = glm::scale(_matrix, glm::vec3(scale));
    return *this;
}

Transformation& Transformation::rotate(const float angle, const glm::vec3 axis) {
    _matrix = glm::rotate(_matrix, angle, axis);
    return *this;
}
