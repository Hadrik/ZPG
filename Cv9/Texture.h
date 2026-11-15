//
// Created by trric on 2026-11-08.
//

#ifndef ZPG_TEXTURE_H
#define ZPG_TEXTURE_H
#include "glad/gl.h"


class Texture {
public:
    explicit Texture(const char* path);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    [[nodiscard]] int getId() const { return static_cast<int>(_id); }
    void bind(GLuint unit) const;

private:
    GLuint _id;
};



#endif //ZPG_TEXTURE_H
