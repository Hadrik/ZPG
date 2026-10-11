//
// Created by trric on 04.10.2026.
//

#include "Transformation.h"

#include "glm/ext/matrix_transform.hpp"
#include <chrono>

Transformation& Transformation::translate(const glm::vec3 translation) {
    _operations.emplace_back([translation] { return glm::translate(glm::mat4(1.0f), translation); });
    return *this;
}

Transformation& Transformation::scale(const glm::vec3 scale) {
    _operations.emplace_back([scale] { return glm::scale(glm::mat4(1.0f), scale); });
    return *this;
}

Transformation& Transformation::scale(const float scale) {
    _operations.emplace_back([scale] { return glm::scale(glm::mat4(1.0f), glm::vec3(scale)); });
    return *this;
}

Transformation& Transformation::rotate(const float angle, const glm::vec3 axis) {
    _operations.emplace_back([angle, axis] { return glm::rotate(glm::mat4(1.0f), angle, axis); });
    return *this;
}

Transformation& Transformation::rotateDynamic(const float speed, const glm::vec3 axis) {
    const auto start = std::chrono::steady_clock::now();
    _operations.emplace_back([speed, axis, start] {
        const auto elapsed = std::chrono::duration<float>(
            std::chrono::steady_clock::now() - start).count();
        return glm::rotate(glm::mat4(1.0f), elapsed * speed, axis);
    });
    return *this;
}

Transformation& Transformation::combine(const Transformation& transformation) {
    const Transformation copy = transformation;
    _operations.emplace_back([copy] {
        return copy.getMatrix();
    });
    return *this;
}

glm::mat4 Transformation::getMatrix() const {
    glm::mat4 result(1.0f);
    for (const auto& operation : _operations) {
        result *= operation();
    }
    return result;
}
