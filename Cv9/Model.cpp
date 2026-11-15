//
// Created by trric on 01.10.2026.
//

#include "Model.h"

using namespace VertexAttributes;

Model::Model(const float *mesh, const GLsizei vertexCount, const Attributes attributes) : _vertexCount(vertexCount) {
    _hasColor = hasAttribute(attributes, Attributes::Color);
    _hasUv = hasAttribute(attributes, Attributes::Uv);

    const GLsizei vertexFloatCount = 6 + (_hasColor ? 3 : 0) + (_hasUv ? 2 : 0);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    const GLsizeiptr size = sizeof(float) * _vertexCount * vertexFloatCount;
    glBufferData(GL_ARRAY_BUFFER, size, mesh, GL_STATIC_DRAW);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    const GLsizei stride = sizeof(float) * vertexFloatCount;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                          reinterpret_cast<void*>(3 * sizeof(float)));

    GLsizei offset = 6;
    if (_hasColor) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride,
                              reinterpret_cast<void*>(offset * sizeof(float)));
        offset += 3;
    } else {
        glDisableVertexAttribArray(2);
        glVertexAttrib3f(2, 0.385f, 0.647f, 0.812f);
    }

    if (_hasUv) {
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride,
                              reinterpret_cast<void*>(offset * sizeof(float)));
    } else {
        glDisableVertexAttribArray(3);
        glVertexAttrib2f(3, 0.0f, 0.0f);
    }
}

Model::Model(Model&& other) noexcept
    : _hasColor(other._hasColor), _hasUv(other._hasUv), _vbo(other._vbo), _vao(other._vao),
      _vertexCount(other._vertexCount) {
    other._vbo = 0;
    other._vao = 0;
    other._vertexCount = 0;
    other._hasColor = false;
    other._hasUv = false;
}

Model& Model::operator=(Model&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);

    _vbo = other._vbo;
    _vao = other._vao;
    _vertexCount = other._vertexCount;
    _hasColor = other._hasColor;
    _hasUv = other._hasUv;

    other._vbo = 0;
    other._vao = 0;
    other._vertexCount = 0;
    other._hasColor = false;
    other._hasUv = false;
    return *this;
}

Model::~Model() {
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}
