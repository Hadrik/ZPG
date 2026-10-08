//
// Created by trric on 04.10.2026.
//

#ifndef ZPG_TRANSFORMATION_H
#define ZPG_TRANSFORMATION_H
#include "glm/vec3.hpp"


class Transformation {
public:
    Transformation() = default;
    ~Transformation() = default;

    float rotation = 0.0f;
    float scale = 1.0f;
    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
};



#endif //ZPG_TRANSFORMATION_H
