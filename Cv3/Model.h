//
// Created by trric on 01.10.2026.
//

#ifndef ZPG_MODEL_H
#define ZPG_MODEL_H
#include "glad/gl.h"


class Model {
public:
    Model(const float* mesh, GLsizei vertexCount);
    ~Model();

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&& other) noexcept;
    Model& operator=(Model&& other) noexcept;

    [[nodiscard]] GLuint VAO() const { return _vao; }
    [[nodiscard]] GLsizei vertexCount() const { return _vertexCount; }

private:
    GLuint _vbo = 0;
    GLuint _vao = 0;
    GLsizei _vertexCount = 0;
};



#endif //ZPG_MODEL_H
