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
    Scene() = default;
    ~Scene() = default;
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene(Scene&&) noexcept = default;
    Scene& operator=(Scene&&) noexcept = delete;

    void addObject(DrawableObject&& object);
    void draw() const;

private:
    std::vector<DrawableObject> _objects;
};



#endif //ZPG_SCENE_H
