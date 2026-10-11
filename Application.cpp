//
// Created by trric on 01.10.2026.
//

#include "Application.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>

#include "Models/sphere.h"
#include "Models/text_mesh.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/triangle.h"
#include "Models/sun.h"
#include "Models/earth.h"
#include "Models/moon.h"

Application::Application() {
    glfwInit();

    _window = glfwCreateWindow(800, 800, "ZPG", nullptr, nullptr);
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

    _shaderBasic = std::make_unique<ShaderProgram>("../VShader.vert", "../FShader.frag");
}

Application::~Application() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Application::prepareScenes() {
    Scene triangleScene(*_shaderBasic);
    DrawableObject translatedTriangle(Model(triangle, 3));
    translatedTriangle.transformation()
        .translate(glm::vec3(-0.45f, 0.0f, 0.0f))
        .rotate(0.6f, glm::vec3(0.0f, 0.0f, 1.0f));
    triangleScene.addObject(std::move(translatedTriangle));

    DrawableObject rotatedTriangle(Model(triangle, 3));
    rotatedTriangle.transformation()
        .rotate(0.6f, glm::vec3(0.0f, 0.0f, 1.0f))
        .translate(glm::vec3(0.45f, 0.0f, 0.0f));
    triangleScene.addObject(std::move(rotatedTriangle));

    DrawableObject tiangleSignature(Model(text_mesh, TEXT_MESH_VERTEX_COUNT));
    tiangleSignature.transformation()
        .translate(glm::vec3(-0.9f, -0.9f, 0.0f))
        .scale(0.1f);
    triangleScene.addObject(std::move(tiangleSignature));
    _scenes.push_back(std::move(triangleScene));

    Scene sphereScene(*_shaderBasic);
    sphereScene.addObject(DrawableObject(Model(sphere, 2880)));
    DrawableObject sphereSignature(Model(text_mesh, TEXT_MESH_VERTEX_COUNT));
    sphereSignature.transformation()
        .translate(glm::vec3(-0.9f, -0.9f, 0.0f))
        .scale(0.1f);
    sphereScene.addObject(std::move(sphereSignature));
    _scenes.push_back(std::move(sphereScene));

    Scene forestScene(*_shaderBasic);
    std::mt19937 generator(42);
    std::uniform_real_distribution<float> xPosition(-1.0f, 1.0f);
    std::uniform_real_distribution<float> yPosition(-0.55f, 0.25f);
    std::uniform_real_distribution<float> treeScale(0.07f, 0.13f);
    for (int i = 0; i < 12; ++i) {
        const glm::vec3 position(xPosition(generator), yPosition(generator), 0.0f);
        DrawableObject treeObject(Model(tree, 92814));
        treeObject.transformation()
            .translate(position)
            .scale(treeScale(generator));
        forestScene.addObject(std::move(treeObject));
    }

    std::uniform_real_distribution<float> bushScale(0.2f, 0.35f);
    for (int i = 0; i < 12; ++i) {
        const glm::vec3 position(xPosition(generator), -0.8f + 0.08f * (i % 2), 0.1f);
        DrawableObject bushObject(Model(bushes, 8730));
        bushObject.transformation()
            .translate(position)
            .scale(bushScale(generator));
        forestScene.addObject(std::move(bushObject));
    }

    DrawableObject forestSunObject(Model(sphere, 2880));
    forestSunObject.transformation()
        .translate(glm::vec3(0.9f, 0.7f, -0.2f))
        .scale(0.2f);
    forestScene.addObject(std::move(forestSunObject));
    DrawableObject forestSignature(Model(text_mesh, TEXT_MESH_VERTEX_COUNT));
    forestSignature.transformation()
        .translate(glm::vec3(-0.9f, -0.9f, 0.0f))
        .scale(0.1f);
    forestScene.addObject(std::move(forestSignature));
    _scenes.push_back(std::move(forestScene));

    Scene solarSystemScene(*_shaderBasic);
    DrawableObject sunObject(Model(sun, 11520, true));
    sunObject.transformation().scale(0.22f);
    solarSystemScene.addObject(std::move(sunObject));

    Transformation earthOrbit;
    earthOrbit
        .rotateDynamic(0.3f, glm::vec3(0.0f, 0.0f, 1.0f))
        .translate(glm::vec3(0.55f, 0.0f, 0.0f));
    DrawableObject earthObject(Model(earth, 11520, true));
    Transformation earthTransform;
    earthTransform
        .combine(earthOrbit)
        .rotate(4.65f, glm::vec3(1.0f, 0.0f, 0.0f))
        .rotateDynamic(-6.f, glm::vec3(0.0f, 1.0f, 0.0f))
        .scale(0.09f);
    earthObject.setTransformation(earthTransform);
    solarSystemScene.addObject(std::move(earthObject));

    Transformation moonTransform;
    moonTransform
        .combine(earthOrbit)
        .rotateDynamic(0.8f, glm::vec3(0.0f, 0.0f, 1.0f))
        .translate(glm::vec3(0.18f, 0.0f, 0.0f))
        .scale(0.025f);
    DrawableObject moonObject(Model(moon, 11520, true));
    moonObject.setTransformation(moonTransform);
    solarSystemScene.addObject(std::move(moonObject));

    DrawableObject solarSignature(Model(text_mesh, TEXT_MESH_VERTEX_COUNT));
    solarSignature.transformation().translate(glm::vec3(-0.9f, -0.9f, 0.0f)).scale(0.1f);
    solarSystemScene.addObject(std::move(solarSignature));
    _scenes.push_back(std::move(solarSystemScene));

    Scene logoScene(*_shaderBasic);
    Model logoModel(text_mesh, TEXT_MESH_VERTEX_COUNT);
    DrawableObject logoObject(std::move(logoModel));
    logoObject.transformation()
        .rotateDynamic(0.5f, glm::vec3(0.0f, 1.0f, 0.0f))
        .scale(0.8f);
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
        } else if (glfwGetKey(_window, GLFW_KEY_5) == GLFW_PRESS) {
            _currentSceneIndex = 4;
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
