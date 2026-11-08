#define GLAD_GL_IMPLEMENTATION
#include <iostream>
#include "Application.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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