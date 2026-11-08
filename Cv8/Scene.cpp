//
// Created by trric on 01.10.2026.
//

#include "Scene.h"

void Scene::addObject(DrawableObject&& object) {
    _objects.push_back(std::move(object));
}

void Scene::addLight(PointLight &&light) {
    _pointLight = std::move(light);
}

void Scene::addSkybox(Skybox&& skybox) {
    _skybox = std::move(skybox);
}

void Scene::draw() const {
    if (_skybox.has_value()) {
        _skybox->draw();
    }
    for (const auto& object : _objects) {
        const auto& shader = object.getShaderOr(_shaderProgram);

        shader.use();
        shader.setIfPresent("lightPosition", _pointLight.getPosition());
        shader.setIfPresent("lightColor", _pointLight.getColor());
        shader.setIfPresent("lightIntensity", _pointLight.getIntensity());
        shader.setIfPresent("lightConstant", _pointLight.getConstant());
        shader.setIfPresent("lightLinear", _pointLight.getLinear());
        shader.setIfPresent("lightQuadratic", _pointLight.getQuadratic());

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
