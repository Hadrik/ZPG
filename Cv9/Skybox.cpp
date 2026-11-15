#include "Skybox.h"

#include <stdexcept>
#include <string>

#include "stb_image.h"

namespace {
constexpr float vertices[] = {
    -1.f,  1.f, -1.f,  -1.f, -1.f, -1.f,   1.f, -1.f, -1.f,
     1.f, -1.f, -1.f,   1.f,  1.f, -1.f,  -1.f,  1.f, -1.f,
    -1.f, -1.f,  1.f,  -1.f, -1.f, -1.f,  -1.f,  1.f, -1.f,
    -1.f,  1.f, -1.f,  -1.f,  1.f,  1.f,  -1.f, -1.f,  1.f,
     1.f, -1.f, -1.f,   1.f, -1.f,  1.f,   1.f,  1.f,  1.f,
     1.f,  1.f,  1.f,   1.f,  1.f, -1.f,   1.f, -1.f, -1.f,
    -1.f, -1.f,  1.f,  -1.f,  1.f,  1.f,   1.f,  1.f,  1.f,
     1.f,  1.f,  1.f,   1.f, -1.f,  1.f,  -1.f, -1.f,  1.f,
    -1.f,  1.f, -1.f,   1.f,  1.f, -1.f,   1.f,  1.f,  1.f,
     1.f,  1.f,  1.f,  -1.f,  1.f,  1.f,  -1.f,  1.f, -1.f,
    -1.f, -1.f, -1.f,  -1.f, -1.f,  1.f,   1.f, -1.f, -1.f,
     1.f, -1.f, -1.f,  -1.f, -1.f,  1.f,   1.f, -1.f,  1.f
};
}

Skybox::Skybox(const ShaderProgram& shader, const std::array<const char*, 6>& faces)
    : _shader(shader) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
    stbi_set_flip_vertically_on_load(false);

    for (unsigned int i = 0; i < faces.size(); ++i) {
        int width = 0;
        int height = 0;
        int channels = 0;
        unsigned char* data = stbi_load(faces[i], &width, &height, &channels, 4);
        if (!data) {
            glDeleteTextures(1, &_texture);
            _texture = 0;
            throw std::runtime_error("Failed to load skybox texture " + std::string(faces[i]));
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
                     width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
}

Skybox::~Skybox() {
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
    glDeleteTextures(1, &_texture);
}

Skybox::Skybox(Skybox&& other) noexcept
    : _shader(other._shader), _vao(other._vao), _vbo(other._vbo), _texture(other._texture) {
    other._vao = 0;
    other._vbo = 0;
    other._texture = 0;
}

Skybox& Skybox::operator=(Skybox&& other) noexcept {
    if (this != &other) {
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
        glDeleteTextures(1, &_texture);
        _vao = other._vao;
        _vbo = other._vbo;
        _texture = other._texture;
        other._vao = 0;
        other._vbo = 0;
        other._texture = 0;
    }
    return *this;
}

void Skybox::draw() const {
    _shader.use();
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
    _shader.setIfPresent("skybox", 0);
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}
