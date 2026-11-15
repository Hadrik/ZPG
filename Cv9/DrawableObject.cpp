//
// Created by trric on 04.10.2026.
//

#include "DrawableObject.h"

void DrawableObject::setTexture(Texture&& texture) {
    _texture = std::move(texture);
}

void DrawableObject::draw(const ShaderProgram& shaderProgram, const unsigned char stencilValue) const {
    const auto shader = _shaderProgram ? _shaderProgram : &shaderProgram;
    shader->use();
    shader->setIfPresent("hasColor", _model.hasColor());
    shader->setIfPresent("hasUv", _model.hasUv());
    if (_texture.has_value()) {
        constexpr GLuint textureUnit = 0;
        _texture.value().bind(textureUnit);
        shader->setIfPresent("textureUnit", static_cast<int>(textureUnit));
    }
    shader->set("modelMatrix", _transformation.getMatrix());

    glBindVertexArray(_model.VAO());
    glStencilFunc(GL_ALWAYS, stencilValue, 0xFF);
    glDrawArrays(GL_TRIANGLES, 0, _model.vertexCount());
}

const ShaderProgram& DrawableObject::getShaderOr(const ShaderProgram& fallback) const {
    return _shaderProgram ? *_shaderProgram : fallback;
}

const std::string& DrawableObject::getName() const {
    return _name;
}
