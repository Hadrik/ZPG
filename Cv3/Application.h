//
// Created by trric on 01.10.2026.
//

#ifndef ZPG_APPLICATION_H
#define ZPG_APPLICATION_H
#include "Scene.h"
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
    std::unique_ptr<ShaderProgram> _shader = nullptr;
    std::vector<Scene> _scenes;
    int _currentSceneIndex{0};

    static void framebuffer_size_callback(GLFWwindow* window, int w, int h);
};



#endif //ZPG_APPLICATION_H
