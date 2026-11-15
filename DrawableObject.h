//
// Created by trric on 04.10.2026.
//

#ifndef ZPG_DRAWABLEOBJECT_H
#define ZPG_DRAWABLEOBJECT_H
#include <optional>

#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Transformation.h"


class DrawableObject {
public:
    explicit DrawableObject(Model&& model, const char* name = nullptr, ShaderProgram* shaderProgram = nullptr)
        : _model(std::move(model)), _name(name ? std::string(name) : "Unnamed"), _shaderProgram(shaderProgram) {}

    ~DrawableObject() = default;

    DrawableObject(const DrawableObject&) = delete;
    DrawableObject& operator=(const DrawableObject&) = delete;
    DrawableObject(DrawableObject&&) noexcept = default;
    DrawableObject& operator=(DrawableObject&&) noexcept = delete;

    Transformation& transformation() { return _transformation; }
    void setTransformation(const Transformation& transformation) { _transformation = transformation; }
    void setTexture(Texture&& texture);
    void draw(const ShaderProgram& shaderProgram, unsigned char stencilValue = 0) const;
    [[nodiscard]] const ShaderProgram& getShaderOr(const ShaderProgram& fallback) const;
    [[nodiscard]] const std::string& getName() const;

private:
    Model _model;
    std::optional<Texture> _texture;
    std::string _name;
    Transformation _transformation{};
    ShaderProgram* _shaderProgram{nullptr};
};


#endif //ZPG_DRAWABLEOBJECT_H
