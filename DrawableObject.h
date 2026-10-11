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
    explicit DrawableObject(Model&& model) : _model(std::move(model)) {};
    ~DrawableObject() = default;

    DrawableObject(const DrawableObject&) = delete;
    DrawableObject& operator=(const DrawableObject&) = delete;
    DrawableObject(DrawableObject&&) noexcept = default;
    DrawableObject& operator=(DrawableObject&&) noexcept = delete;

    Transformation& transformation() { return _transformation; }
    void setTransformation(const Transformation& transformation) { _transformation = transformation; }
    void draw(const ShaderProgram& shader) const;

private:
    Model _model;
    Transformation _transformation{};
};



#endif //ZPG_DRAWABLEOBJECT_H
