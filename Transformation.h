//
// Created by trric on 04.10.2026.
//

#ifndef ZPG_TRANSFORMATION_H
#define ZPG_TRANSFORMATION_H
#include <functional>
#include <vector>

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
    Transformation& rotateDynamic(float speed, glm::vec3 axis);
    Transformation& combine(const Transformation& transformation);

    [[nodiscard]] glm::mat4 getMatrix() const;

private:
    using Operation = std::function<glm::mat4()>;
    std::vector<Operation> _operations;
};



#endif //ZPG_TRANSFORMATION_H
