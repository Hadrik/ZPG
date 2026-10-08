#define GLAD_GL_IMPLEMENTATION
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Application.h"

int main() {
    try {
        Application app;
        app.prepareScenes();
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}