//
// Created by trric on 01.10.2026.
//

#include "Application.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>
#include <chrono>

#include "Models/sphere.h"
#include "Models/text_mesh.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/clock.h"
#include "Models/sun.h"
#include "Models/moon.h"
#include "Models/earth.h"
#include "Models/ship.h"
#include "Models/eb408.h"
#include "Models/chair.h"
#include "Models/table.h"
#include "Models/door.h"
#include "Models/fiona.h"
#include "Models/shrek.h"
#include "Models/board.h"

Application::Application() {
    glfwInit();

    _window = glfwCreateWindow(800, 800, "ZPG", nullptr, nullptr);
    if (!_window) {
        std::cout << "Window creation failed" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, this);
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
    glViewport(0, 0, width, height);
    _camera.resize(width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (const auto app = static_cast<Application*>(glfwGetWindowUserPointer(window))) {
            app->key_callback(key, scancode, action, mods);
        }
    });
    glfwSetCursorPosCallback(_window, [](GLFWwindow* window, const double x, const double y) {
        if (const auto app = static_cast<Application*>(glfwGetWindowUserPointer(window))) {
            app->cursor_position_callback(x, y);
        }
    });
    glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, const int button, const int action, const int mods) {
        if (const auto app = static_cast<Application*>(glfwGetWindowUserPointer(window))) {
            app->mouse_button_callback(button, action, mods);
        }
    });

    _shaderBasic = std::make_unique<ShaderProgram>("../Shaders/Default.vert", "../Shaders/Default.frag");
    _shaderTree = std::make_unique<ShaderProgram>("../Shaders/Tree.vert", "../Shaders/Phong.frag");
    _shaderBush = std::make_unique<ShaderProgram>("../Shaders/Bush.vert", "../Shaders/Bush.frag");
    _shaderClock = std::make_unique<ShaderProgram>("../Shaders/Clock.vert", "../Shaders/Clock.frag");
    _shaderPhong = std::make_unique<ShaderProgram>("../Shaders/Phong.vert", "../Shaders/Phong.frag");
    _shaderAmbient = std::make_unique<ShaderProgram>("../Shaders/Phong.vert", "../Shaders/Ambient.frag");
    _shaderDiffuse = std::make_unique<ShaderProgram>("../Shaders/Phong.vert", "../Shaders/Diffuse.frag");
    _shaderBlinnPhong = std::make_unique<ShaderProgram>("../Shaders/Phong.vert", "../Shaders/BlinnPhong.frag");
    _shaderSkybox = std::make_unique<ShaderProgram>("../Shaders/Skybox.vert", "../Shaders/Skybox.frag");
    _shaderBasic->observe(_camera);
    _shaderTree->observe(_camera);
    _shaderBush->observe(_camera);
    _shaderClock->observe(_camera);
    _shaderPhong->observe(_camera);
    _shaderAmbient->observe(_camera);
    _shaderDiffuse->observe(_camera);
    _shaderBlinnPhong->observe(_camera);
    _shaderSkybox->observe(_camera);
}

Application::~Application() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Application::prepareScenes() {
    Scene classScene(*_shaderPhong);

    DrawableObject roomObject(Model(eb408, eb408_vertex_count, VertexAttributes::Attributes::Uv));
    roomObject.setTexture(Texture("../Textures/eb408.png"));
    roomObject.transformation()
        .rotate(-M_PI / 2, glm::vec3(1.f, 0.f, 0.f));
    classScene.addObject(std::move(roomObject));

    DrawableObject doorObject(Model(door, door_vertex_count, VertexAttributes::Attributes::Uv));
    doorObject.setTexture(Texture("../Textures/door.png"));
    doorObject.transformation()
        .translate(glm::vec3(-2.4f, 0.f, 7.6f))
        .scale(0.011f)
        .rotate(-M_PI / 2, glm::vec3(1.f, 0.f, 0.f));
    classScene.addObject(std::move(doorObject));

    DrawableObject tableObject(Model(table, table_vertex_count, VertexAttributes::Attributes::Uv));
    tableObject.setTexture(Texture("../Textures/table.png"));
    tableObject.transformation()
        .translate(glm::vec3(0.f, 0.f, 3.f))
        .rotate(-M_PI / 2, glm::vec3(1.f, 0.f, 0.f))
        .rotate(M_PI / 2, glm::vec3(0.f, 0.f, 1.f));
    classScene.addObject(std::move(tableObject));

    DrawableObject chairObject(Model(chair, chair_vertex_count, VertexAttributes::Attributes::Uv));
    chairObject.setTexture(Texture("../Textures/chair.png"));
    chairObject.transformation()
        .translate(glm::vec3(1.f, 0.f, 3.f))
        .rotate(-M_PI / 2, glm::vec3(1.f, 0.f, 0.f))
        .rotate(-M_PI / 2, glm::vec3(0.f, 0.f, 1.f));
    classScene.addObject(std::move(chairObject));

    DrawableObject shrekObject(Model(shrek, shrek_vertex_count, VertexAttributes::Attributes::Uv));
    shrekObject.setTexture(Texture("../Textures/shrek.png"));
    shrekObject.transformation()
        .translate(glm::vec3(-2.f, 0.f, 3.f))
        .rotateDynamic(1.f, glm::vec3(0.f, 1.f, 0.f));
    classScene.addObject(std::move(shrekObject));

    DrawableObject fionaObject(Model(fiona, fiona_vertex_count, VertexAttributes::Attributes::Uv));
    fionaObject.setTexture(Texture("../Textures/fiona.png"));
    fionaObject.transformation()
        .translate(glm::vec3(0.5f, 0.f, 3.f))
        .rotate(-M_PI / 2, glm::vec3(0.f, 1.f, 0.f));
    classScene.addObject(std::move(fionaObject));

    DrawableObject boardObject(Model(board, board_vertex_count, VertexAttributes::Attributes::Uv));
    boardObject.setTexture(Texture("../Textures/board.png"));
    boardObject.transformation()
        .translate(glm::vec3(-3.8f, 0.f, 3.f))
        .rotate(-M_PI / 2, glm::vec3(1.f, 0.f, 0.f));
    classScene.addObject(std::move(boardObject));

    DrawableObject signatureObject1(Model(text_mesh, TEXT_MESH_VERTEX_COUNT));
    signatureObject1.transformation()
        .translate(glm::vec3(-1.0f, 0.2f, 1.0f));
    classScene.addObject(std::move(signatureObject1));

    PointLight classLight(glm::vec3(1.0f), 1.0f);
    classLight.transformation().translate(glm::vec3(0.f, 2.f, 4.f));
    classScene.addLight(std::move(classLight));

    classScene.addSkybox(Skybox(*_shaderSkybox, {
        "../Textures/Skybox/posx.jpg",
        "../Textures/Skybox/negx.jpg",
        "../Textures/Skybox/posy.jpg",
        "../Textures/Skybox/negy.jpg",
        "../Textures/Skybox/posz.jpg",
        "../Textures/Skybox/negz.jpg"
    }));

    _scenes.push_back(std::move(classScene));


    Scene singleBallScene(*_shaderPhong);
    DrawableObject ballObject(Model(sphere, 2880));
    ballObject.transformation()
        .translate(glm::vec3(0.0f, 0.0f, 5.0f))
        .scale(1.0f);
    singleBallScene.addObject(std::move(ballObject));
    singleBallScene.setCameraLocation({glm::vec3(0.0f, 0.0f, 10.0f), -90.0f, 0.0f})
        .setBackgroundColor(glm::vec3(0.f, 0.f, 0.f));
    PointLight singleBallLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    singleBallLight.transformation().translate(glm::vec3(0.0f, 0.0f, 5.0f));
    singleBallScene.addLight(std::move(singleBallLight));
    _scenes.push_back(std::move(singleBallScene));

    Scene scaledBallScene(*_shaderPhong);
    DrawableObject scaledBallObject(Model(sphere, 2880));
    scaledBallObject.transformation()
        .translate(glm::vec3(0.0f, 0.0f, 0.0f))
        .scale(glm::vec3(2.0f, 1.0f, 1.0f));
    scaledBallScene.addObject(std::move(scaledBallObject));
    scaledBallScene.setCameraLocation({glm::vec3(0.0f, 0.0f, 10.0f), -90.0f, 0.0f})
        .setBackgroundColor(glm::vec3(0.f, 0.f, 0.f));
    PointLight scaledBallLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    scaledBallLight.transformation().translate(glm::vec3(5.0f, 0.0f, 0.0f));
    scaledBallScene.addLight(std::move(scaledBallLight));
    _scenes.push_back(std::move(scaledBallScene));

    Scene ballsScene(*_shaderPhong);
    const std::tuple<glm::vec3, ShaderProgram*> ballConfigs[] = {
        {glm::vec3(1.0f, 0.0f, 0.0f), _shaderAmbient.get()},
        {glm::vec3(-1.0f, 0.0f, 0.0f), _shaderDiffuse.get()},
        {glm::vec3(0.0f, 1.0f, 0.0f), _shaderPhong.get()},
        {glm::vec3(0.0f, -1.0f, 0.0f), _shaderBlinnPhong.get()}
    };
    for (const auto& config : ballConfigs) {
        // DrawableObject ballObject(Model(sphere, 2880), std::get<1>(config));
        DrawableObject ballObject(Model(sphere, 2880), _shaderPhong.get());
        ballObject.transformation()
            .translate(std::get<0>(config))
            .scale(0.5f);
        ballsScene.addObject(std::move(ballObject));
    }
    ballsScene.setCameraLocation({glm::vec3(0.0f, 0.0f, 5.0f), -90.0f, 0.0f})
        .setBackgroundColor(glm::vec3(0.f, 0.f, 0.f));
    PointLight ballsLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    ballsLight.transformation().translate(glm::vec3(0.0f, 0.0f, 0.0f));
    ballsScene.addLight(std::move(ballsLight));
    _scenes.push_back(std::move(ballsScene));


    Scene planetScene(*_shaderPhong);
    DrawableObject sunObject(Model(sun, 11520, VertexAttributes::Attributes::Color), _shaderAmbient.get());
    sunObject.transformation()
        .translate(glm::vec3(0.0f, 0.0f, 0.0f))
        .scale(1.0f);
    planetScene.addObject(std::move(sunObject));

    Transformation earthTransformation;
    earthTransformation.combine(sunObject.transformation())
        .rotateDynamic(0.1f, glm::vec3(0.f, 1.f, 0.f))
        .translate(glm::vec3(3.0f, 0.0f, 0.0f))
        .scale(0.25f);

    DrawableObject earthObject(Model(earth, 11520, VertexAttributes::Attributes::Color));
    earthObject.transformation()
        .combine(earthTransformation)
        .rotateDynamic(1.f, glm::vec3(0.f, 1.f, 0.f));
    planetScene.addObject(std::move(earthObject));

    DrawableObject moonObject(Model(moon, 11520, VertexAttributes::Attributes::Color));
    moonObject.transformation()
        .combine(earthTransformation)
        .rotateDynamic(0.2f, glm::vec3(0.f, 1.f, 0.f))
        .translate(glm::vec3(2.0f, 0.0f, 0.0f))
        .scale(0.2f);
    planetScene.addObject(std::move(moonObject));

    DrawableObject shipObject(Model(ship, ship_vertex_count, VertexAttributes::Attributes::Color));
    shipObject.transformation()
        .rotateDynamic(0.1f, glm::vec3(1.f, 0.f, 0.f))
        .translate(glm::vec3(0.0f, 0.0f, 3.0f))
        .scale(0.7f);
    planetScene.addObject(std::move(shipObject));

    planetScene.setBackgroundColor(glm::vec3(0.f, 0.f, 0.f))
        .setCameraLocation({glm::vec3(0.0f, 8.0f, 8.0f), -90.0f, -45.0f});
    PointLight planetLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    planetLight.transformation().translate(glm::vec3(0.0f, 0.0f, 0.0f));
    planetScene.addLight(std::move(planetLight));
    _scenes.push_back(std::move(planetScene));


    Scene forestScene(*_shaderPhong);
    constexpr int numTrees = 100;
    constexpr int numBushes = 50;
    constexpr float planeSize = 10.f;
    constexpr float planeR = 0.0f;
    constexpr float planeG = 0.8f;
    constexpr float planeB = 0.0f;

    std::mt19937 generator(0);

    constexpr float plainMesh[] = {
        planeSize, 0.0f,  planeSize, planeR, planeG, planeB, 0.0f, 1.0f, 0.0f,
        planeSize, 0.0f, -planeSize, planeR, planeG, planeB, 0.0f, 1.0f, 0.0f,
       -planeSize, 0.0f, -planeSize, planeR, planeG, planeB, 0.0f, 1.0f, 0.0f,
       -planeSize, 0.0f,  planeSize, planeR, planeG, planeB, 0.0f, 1.0f, 0.0f,
        planeSize, 0.0f,  planeSize, planeR, planeG, planeB, 0.0f, 1.0f, 0.0f,
       -planeSize, 0.0f, -planeSize, planeR, planeG, planeB, 0.0f, 1.0f, 0.0f
    };
    DrawableObject plainObject(Model(plainMesh, 6, VertexAttributes::Attributes::Color));
    forestScene.addObject(std::move(plainObject));

    std::uniform_real_distribution<float> positionDist(-planeSize, planeSize);
    std::uniform_real_distribution<float> treeScaleDist(0.2f, 0.4f);
    std::uniform_real_distribution<float> bushScaleDist(0.3f, 0.8f);

    for (int i = 0; i < numTrees; ++i) {
        const glm::vec3 position(positionDist(generator), 0.0f, positionDist(generator));
        DrawableObject treeObject(Model(tree, 92814), _shaderTree.get());
        treeObject.transformation()
            .translate(position)
            .scale(treeScaleDist(generator));
        forestScene.addObject(std::move(treeObject));
    }

    for (int i = 0; i < numBushes; ++i) {
        const glm::vec3 position(positionDist(generator), 0.0f, positionDist(generator));
        DrawableObject bushObject(Model(bushes, 8730), _shaderBush.get());
        bushObject.transformation()
            .translate(position)
            .scale(bushScaleDist(generator));
        forestScene.addObject(std::move(bushObject));
    }

    glm::vec3 clockPositions[] = {
        glm::vec3(0.f, 0.2f, 0.f),
        glm::vec3(1.f, 0.2f, 1.f)
    };
    for (const auto& position : clockPositions) {
        DrawableObject clockObject(Model(clockModel, 44826, VertexAttributes::Attributes::Color), _shaderClock.get());
        clockObject.transformation()
            .translate(position)
            .rotate(3.14f, glm::vec3(0.f, 1.f, 0.f))
            .scale(glm::vec3(-0.2f, 0.2f, 0.2f));
        forestScene.addObject(std::move(clockObject));
    }

    DrawableObject forestLightObject(Model(sun, 11520, VertexAttributes::Attributes::Color), _shaderAmbient.get());
    forestLightObject.transformation()
        .rotateDynamic(0.3f, glm::vec3(0.f, 1.f, 0.f))
        .translate(glm::vec3(3.0f, 1.0f, 0.0f))
        .scale(0.1f);
    forestScene.addObject(std::move(forestLightObject));
    PointLight forestLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
    forestLight.transformation().combine(forestLightObject.transformation());
    forestScene.addLight(std::move(forestLight));

    DrawableObject signatureObject(Model(text_mesh, TEXT_MESH_VERTEX_COUNT));
    signatureObject.transformation()
        .translate(glm::vec3(-1.0f, 5.0f, 0.2f))
        .scale(1.0f);
    forestScene.addObject(std::move(signatureObject));

    forestScene.setCameraLocation({glm::vec3(0.0f, 2.0f, 5.0f), -90.0f, -20.0f})
        .setBackgroundColor(glm::vec3(0.f, 0.f, 0.05f));

    _scenes.push_back(std::move(forestScene));


    Scene textureScene(*_shaderPhong);
    constexpr float texturedPlain[] = {
        1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
       -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

       -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
       -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
    };

    DrawableObject texturedPlainObject(Model(texturedPlain, 6, VertexAttributes::Attributes::Uv));
    texturedPlainObject.setTexture(Texture("../Textures/wooden_fence.jpg"));
    textureScene.addObject(std::move(texturedPlainObject));

    PointLight textureLight(glm::vec3(1.0f), 1.f);
    textureLight.transformation().translate(glm::vec3(0.0f, 1.0f, 0.0f));
    textureScene.addLight(std::move(textureLight));

    textureScene.addSkybox(Skybox(*_shaderSkybox, {
        "../Textures/Skybox/posx.jpg",
        "../Textures/Skybox/negx.jpg",
        "../Textures/Skybox/posy.jpg",
        "../Textures/Skybox/negy.jpg",
        "../Textures/Skybox/posz.jpg",
        "../Textures/Skybox/negz.jpg"
    }));

    textureScene.setBackgroundColor(glm::vec3(0.f, 0.f, 0.f));
    _scenes.push_back(std::move(textureScene));
}

void Application::run() {
    if (_scenes.empty()) {
        std::cout << "No scenes prepared. Exiting." << std::endl;
        return;
    }
    _currentScene = &_scenes.front();
    _camera.setTransform(_currentScene->getCameraLocation());

    while (!glfwWindowShouldClose(_window)) {
        static auto previousFrame = std::chrono::steady_clock::now();
        const auto currentFrame = std::chrono::steady_clock::now();
        const float deltaTime = std::chrono::duration<float>(currentFrame - previousFrame).count();
        previousFrame = currentFrame;
        process_camera_input(deltaTime);
        const auto bg = _currentScene->getBackgroundColor();
        glClearColor(bg.r, bg.g, bg.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _shaderClock->use();
        _shaderClock->set("elapsedTime", static_cast<float>(glfwGetTime())); // For clock shader
        _currentScene->draw();

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void Application::process_camera_input(const float deltaTime) {
    _camera.move(deltaTime,
        glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS,
        glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS,
        glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS,
        glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS,
        glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS,
        glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS);
}

void Application::cursor_position_callback(const double x, const double y) {
    if (_rightMouseHeld) {
        _camera.rotate(static_cast<float>(x - _lastMouseX), static_cast<float>(_lastMouseY - y));
    }
    _lastMouseX = x;
    _lastMouseY = y;
}

void Application::mouse_button_callback(const int button, const int action, const int) {
    if (button != GLFW_MOUSE_BUTTON_RIGHT) {
        return;
    }

    _rightMouseHeld = action == GLFW_PRESS;
    if (_rightMouseHeld) {
        glfwGetCursorPos(_window, &_lastMouseX, &_lastMouseY);
    }
}

void Application::cycleScenes() {
    _currentSceneIndex = (_currentSceneIndex + 1) % _scenes.size();
    _currentScene = &_scenes[_currentSceneIndex];
    _camera.setTransform(_currentScene->getCameraLocation());
}

void Application::key_callback(const int key, const int scancode, const int action, const int mods) {
    if (action != GLFW_PRESS) {
        return;
    }

    switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(_window, GLFW_TRUE);
            break;
        case GLFW_KEY_SPACE:
            cycleScenes();
            break;
        default:
            break;
    }
}

void Application::framebuffer_size_callback(GLFWwindow *window, int w, int h) {
    glViewport(0, 0, w, h);
    if (const auto app = static_cast<Application*>(glfwGetWindowUserPointer(window))) {
        app->_camera.resize(w, h);
    }
}
