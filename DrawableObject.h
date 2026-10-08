//
// Created by trric on 04.10.2026.
//

#ifndef ZPG_DRAWABLEOBJECT_H
#define ZPG_DRAWABLEOBJECT_H
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"


class DrawableObject {
public:
    explicit DrawableObject(Model&& model, const ShaderProgram& shaderProgram)
        : _model(std::move(model)), _shaderProgram(shaderProgram) {};
    ~DrawableObject() = default;

    DrawableObject(const DrawableObject&) = delete;
    DrawableObject& operator=(const DrawableObject&) = delete;
    DrawableObject(DrawableObject&&) noexcept = default;
    DrawableObject& operator=(DrawableObject&&) noexcept = delete;

    [[nodiscard]] Transformation& transformation() { return _transformation; }
    void draw() const;

private:
    Model _model;
    Transformation _transformation{};
    const ShaderProgram& _shaderProgram;
};



#endif //ZPG_DRAWABLEOBJECT_H
