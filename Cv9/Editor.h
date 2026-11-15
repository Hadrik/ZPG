//
// Created by trric on 2026-11-15.
//

#ifndef ZPG_EDITOR_H
#define ZPG_EDITOR_H
#include "Scene.h"
#include "Camera.h"

class Editor {
public:
    Editor(const Camera& camera, const int windowHeight) : _camera(camera), _windowHeight(windowHeight) {}

    void setScene(Scene* scene);
    void setWindowSize(int windowWidth, int windowHeight);

    void click(int x, int y, bool placeObject = false);
    void process();

private:
    const Camera& _camera;
    Scene* _scene {nullptr};
    std::vector<DrawableObject> _objects;
    int _windowHeight {0};
    int _windowWidth {0};
    int _clickX {0};
    int _clickY {0};
    bool _clicked {false};
    bool _place {false};
};



#endif //ZPG_EDITOR_H
