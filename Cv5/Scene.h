//
// Created by trric on 01.10.2026.
//

#ifndef ZPG_SCENE_H
#define ZPG_SCENE_H

#include <glad/gl.h>
#include <vector>

#include "DrawableObject.h"
#include "ShaderProgram.h"

class Scene {
public:
    explicit Scene(const ShaderProgram& shaderProgram) : _shaderProgram(shaderProgram) {}
    ~Scene() = default;
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene(Scene&&) noexcept = default;
    Scene& operator=(Scene&&) noexcept = delete;

    void addObject(DrawableObject&& object);
    void draw() const;

private:
    std::vector<DrawableObject> _objects;
    const ShaderProgram& _shaderProgram;
};



#endif //ZPG_SCENE_H
