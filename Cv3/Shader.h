//
// Created by trric on 04.10.2026.
//

#ifndef ZPG_SHADER_H
#define ZPG_SHADER_H
#include "glad/gl.h"


class Shader {
public:
    Shader(const char* path, GLenum type);
    ~Shader();

    [[nodiscard]] GLuint id() const { return _id; }

private:
    GLuint _id;
};



#endif //ZPG_SHADER_H
