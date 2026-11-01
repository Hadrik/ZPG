//
// Created by trric on 01.10.2026.
//

#ifndef ZPG_MODEL_H
#define ZPG_MODEL_H
#include "glad/gl.h"


class Model {
public:
    Model(const float* mesh, GLsizei vertexCount, bool withColor = false);
    ~Model();

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&& other) noexcept;
    Model& operator=(Model&& other) noexcept;

    [[nodiscard]] GLuint VAO() const { return _vao; }
    [[nodiscard]] GLsizei vertexCount() const { return _vertexCount; }
    [[nodiscard]] bool hasColor() const { return _hasColor; }

private:
    bool _hasColor = false;
    GLuint _vbo = 0;
    GLuint _vao = 0;
    GLsizei _vertexCount = 0;
};



#endif //ZPG_MODEL_H
