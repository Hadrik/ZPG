//
// Created by trric on 18.10.2026.
//

#include "Camera.h"

#include <cmath>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"

Camera::Camera()
    : _position(0.0f, 0.0f, 3.0f),
      _front(0.0f, 0.0f, -1.0f),
      _up(0.0f, 1.0f, 0.0f),
      _yaw(-90.0f),
      _pitch(0.0f),
      _aspectRatio(1.0f) {}

void Camera::addObserver(ICameraObserver& observer) {
    if (std::find(_observers.begin(), _observers.end(), &observer) == _observers.end()) {
        _observers.push_back(&observer);
        observer.onCameraChanged(getViewMatrix(), getProjectionMatrix());
    }
}

void Camera::removeObserver(ICameraObserver& observer) {
    _observers.erase(std::remove(_observers.begin(), _observers.end(), &observer), _observers.end());
}

void Camera::move(const float deltaTime, const bool forward, const bool backward,
                  const bool left, const bool right, const bool up, const bool down) {
    const float velocity = 2.5f * deltaTime;
    const glm::vec3 rightDirection = glm::normalize(glm::cross(_front, _up));
    glm::vec3 movement(0.0f);
    if (forward) movement += _front;
    if (backward) movement -= _front;
    if (left) movement -= rightDirection;
    if (right) movement += rightDirection;
    if (up) movement += _up;
    if (down) movement -= _up;

    if (glm::length(movement) > 0.0f) {
        _position += glm::normalize(movement) * velocity;
        notifyObservers();
    }
}

void Camera::rotate(const float xOffset, const float yOffset) {
    constexpr float sensitivity = 0.1f;
    _yaw += xOffset * sensitivity;
    _pitch = std::clamp(_pitch + yOffset * sensitivity, -89.0f, 89.0f);
    updateFront();
    notifyObservers();
}

void Camera::resize(const int width, const int height) {
    if (height <= 0) {
        return;
    }
    _aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    notifyObservers();
}

void Camera::setTransform(const CameraLocation &location) {
    _position = location.position;
    _yaw = location.yaw;
    _pitch = std::clamp(location.pitch, -89.0f, 89.0f);
    updateFront();
    notifyObservers();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(45.0f), _aspectRatio, 0.1f, 100.0f);
}

void Camera::notifyObservers() const {
    const glm::mat4 view = getViewMatrix();
    const glm::mat4 projection = getProjectionMatrix();
    for (auto* observer : _observers) {
        observer->onCameraChanged(view, projection);
    }
}

void Camera::updateFront() {
    const glm::vec3 direction(
        std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch)),
        std::sin(glm::radians(_pitch)),
        std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch)));
    _front = glm::normalize(direction);
}
