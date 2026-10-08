//
// Created by trric on 04.10.2026.
//

#include "DrawableObject.h"

void DrawableObject::draw() const {
    _shaderProgram.use();
    _shaderProgram.set("rotation", _transformation.rotation);
    _shaderProgram.set("scale", _transformation.scale);
    _shaderProgram.set("translation", _transformation.translation);

    glBindVertexArray(_model.VAO());
    glDrawArrays(GL_TRIANGLES, 0, _model.vertexCount());
}
