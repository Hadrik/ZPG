//
// Created by trric on 04.10.2026.
//

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "glad/gl.h"

Shader::Shader(const char *path, const GLenum type) {
    if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER) {
        throw std::runtime_error("Invalid shader type");
    }

    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Failed to open shader file");
    }

    std::stringstream source;
    source << file.rdbuf();
    const std::string sourceString = source.str();
    const char *sourceCode = sourceString.c_str();

    _id = glCreateShader(type);
    if (_id == 0) {
        throw std::runtime_error("Failed to create shader");
    }

    glShaderSource(_id, 1, &sourceCode, nullptr);
    glCompileShader(_id);

    GLint compiled = GL_FALSE;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        GLint logLength = 0;
        glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &logLength);

        std::string log(static_cast<size_t>(logLength), '\0');
        if (logLength > 0) {
            glGetShaderInfoLog(_id, logLength, nullptr, log.data());
        }

        glDeleteShader(_id);
        throw std::runtime_error("Shader compilation failed: " + log);
    }
}

Shader::~Shader() {
    glDeleteShader(_id);
}
