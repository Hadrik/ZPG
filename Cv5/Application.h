//
// Created by trric on 01.10.2026.
//

#ifndef ZPG_APPLICATION_H
#define ZPG_APPLICATION_H
#include "Scene.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "GLFW/glfw3.h"
#include <memory>
#include <vector>


class Application {
public:
    Application();
    ~Application();

    void prepareScenes();
    void run();

private:
    GLFWwindow* _window;
    Camera _camera;
    std::unique_ptr<ShaderProgram> _shaderBasic = nullptr;
    std::unique_ptr<ShaderProgram> _shaderTree = nullptr;
    std::unique_ptr<ShaderProgram> _shaderBush = nullptr;
    std::unique_ptr<ShaderProgram> _shaderClock = nullptr;
    double _lastMouseX{0.0};
    double _lastMouseY{0.0};
    bool _rightMouseHeld{false};

    std::vector<Scene> _scenes;
    int _currentSceneIndex{0};
    Scene* _currentScene{nullptr};

    void cycleScenes();
    void key_callback(int key, int scancode, int action, int mods);
    void cursor_position_callback(double x, double y);
    void mouse_button_callback(int button, int action, int mods);
    void process_camera_input(float deltaTime);
    static void framebuffer_size_callback(GLFWwindow* window, int w, int h);
};



#endif //ZPG_APPLICATION_H
