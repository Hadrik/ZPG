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
    explicit DrawableObject(Model&& model, ShaderProgram* shaderProgram = nullptr) : _model(std::move(model)), _shaderProgram(shaderProgram) {};
    ~DrawableObject() = default;

    DrawableObject(const DrawableObject&) = delete;
    DrawableObject& operator=(const DrawableObject&) = delete;
    DrawableObject(DrawableObject&&) noexcept = default;
    DrawableObject& operator=(DrawableObject&&) noexcept = delete;

    Transformation& transformation() { return _transformation; }
    void setTransformation(const Transformation& transformation) { _transformation = transformation; }
    void draw(const ShaderProgram& shaderProgram) const;
    [[nodiscard]] const ShaderProgram& getShaderOr(const ShaderProgram& fallback) const;

private:
    Model _model;
    Transformation _transformation{};
    ShaderProgram* _shaderProgram{nullptr};
};



#endif //ZPG_DRAWABLEOBJECT_H
