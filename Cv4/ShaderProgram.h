#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <string>
#include <glm/glm.hpp>

#include "Shader.h"

class ShaderProgram {
public:
    explicit ShaderProgram(const char* vertex_path, const char* fragment_path);
    ~ShaderProgram();

    [[nodiscard]] GLuint id() const { return _id; }
    void use() const;
    void set(const std::string& name, bool value) const;
    void set(const std::string& name, int value) const;
    void set(const std::string& name, float value) const;
    void set(const std::string& name, glm::mat4 value) const;
    void set(const std::string& name, glm::vec3 value) const;

private:
    GLuint _id;
    Shader _vertexShader, _fragmentShader;

    [[nodiscard]] GLint getLocation(const std::string& name) const;
};

#endif //SHADER_H
