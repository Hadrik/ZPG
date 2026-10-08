#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const char *vertex_path, const char *fragment_path) :
_vertexShader(vertex_path, GL_VERTEX_SHADER),
_fragmentShader(fragment_path, GL_FRAGMENT_SHADER) {
    _id = glCreateProgram();
    glAttachShader(_id, _vertexShader.id());
    glAttachShader(_id, _fragmentShader.id());
    glLinkProgram(_id);

    GLint linked = GL_FALSE;
    glGetProgramiv(_id, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
        GLint logLength = 0;
        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);

        std::string log(static_cast<size_t>(logLength), '\0');
        if (logLength > 0) {
            glGetProgramInfoLog(_id, logLength, nullptr, log.data());
        }

        glDeleteProgram(_id);
        throw std::runtime_error("Shader program linking failed: " + log);
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(_id);
}

void ShaderProgram::use() const {
    glUseProgram(_id);
}

void ShaderProgram::set(const std::string &name, const bool value) const {
    glUniform1i(getLocation(name), static_cast<int>(value));
}

void ShaderProgram::set(const std::string &name, const int value) const {
    glUniform1i(getLocation(name), value);
}

void ShaderProgram::set(const std::string &name, const float value) const {
    glUniform1f(getLocation(name), value);
}

void ShaderProgram::set(const std::string &name, glm::mat4 value) const {
    glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::set(const std::string &name, glm::vec3 value) const {
    glUniform3fv(getLocation(name), 1, glm::value_ptr(value));
}

GLint ShaderProgram::getLocation(const std::string &name) const {
    const GLint location = glGetUniformLocation(_id, name.c_str());
    if (location == -1) {
        throw std::runtime_error("Invalid uniform location \'" + name + "\'");
    }
    return location;
}
