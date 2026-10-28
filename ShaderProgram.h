#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <string>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"

class ShaderProgram : public ICameraObserver {
public:
    explicit ShaderProgram(const char* vertex_path, const char* fragment_path);
    ~ShaderProgram() override;

    void observe(Camera& camera);
    void onCameraChanged(const glm::mat4& view, const glm::mat4& projection) override;
    [[nodiscard]] GLuint id() const { return _id; }
    void use() const;
    void set(const std::string& name, bool value) const;
    void set(const std::string& name, int value) const;
    void set(const std::string& name, float value) const;
    void set(const std::string& name, glm::mat4 value) const;
    void set(const std::string& name, glm::vec3 value) const;
    void setIfPresent(const std::string& name, glm::mat4 value) const;
    void setIfPresent(const std::string& name, glm::vec3 value) const;
    void setIfPresent(const std::string& name, float value) const;
    void setIfPresent(const std::string& name, bool value) const;

private:
    GLuint _id;
    Shader _vertexShader, _fragmentShader;
    Camera* _camera{nullptr};
    glm::mat4 _viewMatrix{1.0f};
    glm::mat4 _projectionMatrix{1.0f};

    [[nodiscard]] GLint getLocation(const std::string& name) const;
};

#endif //SHADER_H
