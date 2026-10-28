//
// Created by trric on 01.10.2026.
//

#include "Scene.h"

void Scene::addObject(DrawableObject&& object) {
    _objects.push_back(std::move(object));
}

void Scene::addLight(const PointLight &light) {
    _pointLight = light;
}

void Scene::draw() const {
    for (const auto& object : _objects) {
        const auto& shader = object.getShaderOr(_shaderProgram);

        shader.use();
        if (_pointLight) {
            shader.setIfPresent("lightPosition", _pointLight->getPosition());
            shader.setIfPresent("lightColor", _pointLight->getColor());
            shader.setIfPresent("lightIntensity", _pointLight->getIntensity());
        }

        object.draw(shader);
    }
}

Scene & Scene::setCameraLocation(const CameraLocation &location) {
    _cameraLocation = location;
    return *this;
}

Scene & Scene::setBackgroundColor(const glm::vec3 &color) {
    _bgColor = color;
    return *this;
}
