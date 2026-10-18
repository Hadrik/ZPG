//
// Created by trric on 01.10.2026.
//

#include "Model.h"

Model::Model(const float *mesh, const GLsizei vertexCount, const bool withColor) : _vertexCount(vertexCount) {
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertexCount * (withColor ? 9 : 6), mesh, GL_STATIC_DRAW);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    if (withColor) {
        glEnableVertexAttribArray(2);
    }
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    GLsizei stride = sizeof(float) * (withColor ? 9 : 6);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(float)));
    if (withColor) {
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6 * sizeof(float)));
    }
}

Model::Model(Model&& other) noexcept
    : _vbo(other._vbo), _vao(other._vao), _vertexCount(other._vertexCount) {
    other._vbo = 0;
    other._vao = 0;
    other._vertexCount = 0;
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

    other._vbo = 0;
    other._vao = 0;
    other._vertexCount = 0;
    return *this;
}

Model::~Model() {
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}
