//
// Created by trric on 01.10.2026.
//

#include "Application.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Models/sphere.h"
#include "Models/text_mesh.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/triangle.h"

Application::Application() {
    glfwInit();

    _window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
    if (!_window) {
        std::cout << "Window creation failed" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    if (!gladLoadGL((GLADloadfunc) glfwGetProcAddress)) {
        std::cout << "glfw initialization failed" << std::endl;
        glfwTerminate();
        return;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    std::cout << "GLFW Version: " << major << "." << minor << "." << revision << std::endl;

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    const float ratio = width / static_cast<float>(height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glEnable(GL_DEPTH_TEST);

    _shader = std::make_unique<ShaderProgram>("../VShader.vert", "../FShader.frag");
}

Application::~Application() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Application::prepareScenes() {
    Scene triangleScene{};
    triangleScene.addObject(DrawableObject(Model(triangle, 3), *_shader));
    DrawableObject tiangleSignature(Model(text_mesh, TEXT_MESH_VERTEX_COUNT), *_shader);
    tiangleSignature.transformation()
        .scale(0.1f)
        .translate(glm::vec3(-0.9f, -0.9f, 0.0f));
    triangleScene.addObject(std::move(tiangleSignature));
    _scenes.push_back(std::move(triangleScene));

    Scene sphereScene{};
    sphereScene.addObject(DrawableObject(Model(sphere, 2880), *_shader));
    DrawableObject sphereSignature(Model(text_mesh, TEXT_MESH_VERTEX_COUNT), *_shader);
    sphereSignature.transformation()
        .scale(0.1f)
        .translate(glm::vec3(-0.9f, -0.9f, 0.0f));
    sphereScene.addObject(std::move(sphereSignature));
    _scenes.push_back(std::move(sphereScene));

    Scene forestScene{};
    const glm::vec3 treePositions[] = {
        {-0.95f, -0.55f, 0.0f}, {-0.65f, -0.50f, 0.0f},
        {-0.35f, -0.55f, 0.0f}, {-0.05f, -0.50f, 0.0f},
        { 0.25f, -0.55f, 0.0f}, { 0.55f, -0.50f, 0.0f},
        { 0.85f, -0.55f, 0.0f}, {-0.80f, -0.15f, 0.0f},
        { 0.00f, -0.10f, 0.0f}, { 0.70f, -0.15f, 0.0f}
    };
    for (const auto& position : treePositions) {
        DrawableObject treeObject(Model(tree, 92814), *_shader);
        treeObject.transformation()
            .scale(0.1f)
            .translate(position);
        forestScene.addObject(std::move(treeObject));
    }

    const glm::vec3 bushPositions[] = {
        {-1.05f, -0.85f, 0.1f}, {-0.80f, -0.82f, 0.1f},
        {-0.55f, -0.88f, 0.1f}, {-0.30f, -0.84f, 0.1f},
        {-0.05f, -0.87f, 0.1f}, { 0.20f, -0.83f, 0.1f},
        { 0.45f, -0.88f, 0.1f}, { 0.70f, -0.84f, 0.1f},
        { 0.95f, -0.87f, 0.1f}, {-0.95f, -0.25f, 0.1f}
    };
    for (const auto& position : bushPositions) {
        DrawableObject bushObject(Model(bushes, 8730), *_shader);
        bushObject.transformation()
            .scale(0.3f)
            .translate(position);
        forestScene.addObject(std::move(bushObject));
    }

    DrawableObject sunObject(Model(sphere, 2880), *_shader);
    sunObject.transformation()
        .scale(0.2f)
        .translate(glm::vec3(0.9f, 0.7f, -0.2f));
    forestScene.addObject(std::move(sunObject));
    DrawableObject forestSignature(Model(text_mesh, TEXT_MESH_VERTEX_COUNT), *_shader);
    forestSignature.transformation()
        .scale(0.1f)
        .translate(glm::vec3(-0.9f, -0.9f, 0.0f));
    forestScene.addObject(std::move(forestSignature));
    _scenes.push_back(std::move(forestScene));

    Scene logoScene{};
    Model logoModel(text_mesh, TEXT_MESH_VERTEX_COUNT);
    DrawableObject logoObject(std::move(logoModel), *_shader);
    logoObject.transformation()
        .scale(0.1f)
        .rotate(0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
    logoScene.addObject(std::move(logoObject));
    _scenes.push_back(std::move(logoScene));
}

void Application::run() {
    while (!glfwWindowShouldClose(_window)) {

        if (glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS) {
            _currentSceneIndex = 0;
        } else if (glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS) {
            _currentSceneIndex = 1;
        } else if (glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS) {
            _currentSceneIndex = 2;
        } else if (glfwGetKey(_window, GLFW_KEY_4) == GLFW_PRESS) {
            _currentSceneIndex = 3;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _scenes[_currentSceneIndex].draw();

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void Application::framebuffer_size_callback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
}
