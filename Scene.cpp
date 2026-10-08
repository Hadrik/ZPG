//
// Created by trric on 01.10.2026.
//

#include "Scene.h"

void Scene::addObject(DrawableObject&& object) {
    _objects.push_back(std::move(object));
}

void Scene::draw() const {
    for (const auto& object : _objects) {
        object.draw();
    }
}
