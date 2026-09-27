#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    explicit Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();

    [[nodiscard]] unsigned int id() const;
    [[nodiscard]] bool has_error() const;
    void use() const;
    void set(const std::string& name, bool value) const;
    void set(const std::string& name, int value) const;
    void set(const std::string& name, float value) const;
    void set(const std::string& name, glm::mat4 value) const;

private:
    unsigned int _id;
    bool _error = false;
};

#endif //SHADER_H
