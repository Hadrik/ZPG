//
// Created by trric on 01.10.2026.
//

#ifndef ZPG_SCENE_H
#define ZPG_SCENE_H

#include <optional>
#include <glad/gl.h>
#include <vector>

#include "DrawableObject.h"
#include "PointLight.h"
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
    void addLight(const PointLight& light);
    void draw() const;

    Scene& setCameraLocation(const CameraLocation& location);
    [[nodiscard]] CameraLocation getCameraLocation() const { return _cameraLocation; }

    Scene& setBackgroundColor(const glm::vec3& color);
    [[nodiscard]] glm::vec3 getBackgroundColor() const { return _bgColor; }

private:
    std::vector<DrawableObject> _objects;
    std::optional<PointLight> _pointLight;
    CameraLocation _cameraLocation {glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f};
    glm::vec3 _bgColor = glm::vec3(1.0f, 1.0f, 1.0f);
    const ShaderProgram& _shaderProgram;
};



#endif //ZPG_SCENE_H
