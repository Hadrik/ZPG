//
// Created by trric on 18.10.2026.
//

#ifndef ZPG_CAMERA_H
#define ZPG_CAMERA_H
#include <algorithm>
#include <vector>

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

struct CameraLocation {
    glm::vec3 position;
    float yaw;
    float pitch;
};

class ICameraObserver {
public:
    virtual ~ICameraObserver() = default;
    virtual void onCameraChanged(const glm::mat4& view, const glm::mat4& projection) = 0;
};

class Camera {
public:
    Camera();
    ~Camera() = default;

    void addObserver(ICameraObserver& observer);
    void removeObserver(ICameraObserver& observer);

    void move(float deltaTime, bool forward, bool backward, bool left, bool right, bool up, bool down);
    void rotate(float xOffset, float yOffset);
    void resize(int width, int height);
    void setTransform(const CameraLocation& location);

    [[nodiscard]] glm::mat4 getViewMatrix() const;
    [[nodiscard]] glm::mat4 getProjectionMatrix() const;
    [[nodiscard]] CameraLocation getTransform() const { return {_position, _yaw, _pitch}; }

private:
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    float _yaw;
    float _pitch;
    float _aspectRatio;
    std::vector<ICameraObserver*> _observers;

    void notifyObservers() const;
    void updateFront();
};



#endif //ZPG_CAMERA_H
