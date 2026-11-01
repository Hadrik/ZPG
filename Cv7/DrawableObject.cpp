//
// Created by trric on 04.10.2026.
//

#include "DrawableObject.h"

void DrawableObject::draw(const ShaderProgram& shaderProgram) const {
    const auto shader = _shaderProgram ? _shaderProgram : &shaderProgram;
    shader->use();
    shader->setIfPresent("hasColor", _model.hasColor());
    shader->set("modelMatrix", _transformation.getMatrix());

    glBindVertexArray(_model.VAO());
    glDrawArrays(GL_TRIANGLES, 0, _model.vertexCount());
}

const ShaderProgram & DrawableObject::getShaderOr(const ShaderProgram &fallback) const {
    return _shaderProgram ? *_shaderProgram : fallback;
}
