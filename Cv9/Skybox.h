#ifndef ZPG_SKYBOX_H
#define ZPG_SKYBOX_H

#include <array>

#include "ShaderProgram.h"

class Skybox {
public:
    Skybox(const ShaderProgram& shader, const std::array<const char*, 6>& faces);
    ~Skybox();

    Skybox(const Skybox&) = delete;
    Skybox& operator=(const Skybox&) = delete;
    Skybox(Skybox&& other) noexcept;
    Skybox& operator=(Skybox&& other) noexcept;

    void draw() const;

private:
    const ShaderProgram& _shader;
    GLuint _vao{0};
    GLuint _vbo{0};
    GLuint _texture{0};
};

#endif // ZPG_SKYBOX_H
