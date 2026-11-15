//
// Created by trric on 2026-11-08.
//

#include "Texture.h"

#include <iostream>

#include "stb_image.h"

Texture::Texture(const char *path) {
    int text_width, text_height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &text_width, &text_height, &channels, 4);
    if (!data) {
        throw std::runtime_error("Failed to load texture" + std::string(path));
    }
    glActiveTexture(GL_TEXTURE0);
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    _id = tex;
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

Texture::Texture(Texture &&other) noexcept
    : _id(other._id) {
    other._id = 0;
}

Texture& Texture::operator=(Texture &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    glDeleteTextures(1, &_id);

    _id = other._id;
    other._id = 0;
    return *this;
}

void Texture::bind(const GLuint unit) const {
    glBindTextureUnit(unit, _id);
}
