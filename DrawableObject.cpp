//
// Created by trric on 04.10.2026.
//

#include "DrawableObject.h"

void DrawableObject::draw(const ShaderProgram& shader) const {
    shader.use();
    shader.set("modelMatrix", _transformation.getMatrix());

    glBindVertexArray(_model.VAO());
    glDrawArrays(GL_TRIANGLES, 0, _model.vertexCount());
}
