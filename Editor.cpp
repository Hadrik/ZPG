//
// Created by trric on 2026-11-15.
//

#include "Editor.h"

#include <iostream>

#include "glm/ext/matrix_projection.hpp"
#include "Models/chair.h"

void Editor::setScene(Scene* scene) {
    _scene = scene;
}

void Editor::setWindowSize(const int windowWidth, const int windowHeight) {
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
}

void Editor::click(const int x, const int y, const bool placeObject) {
    _clickX = x;
    _clickY = y;
    _clicked = true;
    _place = placeObject;
}

void Editor::process() {
    if (!_clicked) return;
    _clicked = false;

    const auto x = static_cast<GLint>(_clickX);
    const auto y = static_cast<GLint>(_windowHeight - _clickY - 1.0);

    GLuint id;
    glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &id);

    GLfloat depth;
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    const glm::vec3 point = {x, y, depth};
    const glm::vec4 viewport = {0, 0, _windowWidth, _windowHeight};
    const glm::vec3 position = glm::unProject(
            point,
            _camera.getViewMatrix(),
            _camera.getProjectionMatrix(),
            viewport
    );

    std::cout << "Clicked object - Window [" << _clickX << ", " << _clickY << ", " << depth
            << "] - World [" << position.x << ", " << position.y << ", " << position.z << "] : "
            << _scene->getObject(id).getName() << " (" << id << ")" << std::endl;

    if (_place) {
        DrawableObject newObject(Model(chair, chair_vertex_count, VertexAttributes::Attributes::Uv), "placed chair");
        newObject.setTexture(Texture("../Textures/chair.png"));
        newObject.transformation()
                .translate(position)
                .rotate(-M_PI / 2, glm::vec3(1.f, 0.f, 0.f));
        _scene->addObject(std::move(newObject));
    }
}
