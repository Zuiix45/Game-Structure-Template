#include "Camera.h"

#include "../sys/Engine.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float x, float y, float width, float height, float zoom) 
    : x(x), y(y), width(width), height(height), zoom(zoom) {
    
    calculateProjectionMatrix();
}

void Camera::follow(unsigned int objectID) {
    auto object = engine::getObject(objectID);

    if (object != nullptr) {
        x = -object->getX() + xOffset;
        y = -object->getY() + yOffset;
    }
}

glm::mat4 Camera::getViewMatrix() {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
    return projectionMatrix;
}

void Camera::calculateViewMatrix() {
    auto translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, 0.0f));

    viewMatrix = translation * scale;
}

void Camera::calculateProjectionMatrix() {
    projectionMatrix = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
}

void Camera::setX(float x) { this->x = x; }
void Camera::setY(float y) { this->y = y; }
void Camera::setXOffset(float xOffset) { this->xOffset = xOffset; }
void Camera::setYOffset(float yOffset) { this->yOffset = yOffset; }
void Camera::setZoom(float zoom) { this->zoom = zoom; }

void Camera::setWidth(float width) {
    this->width = width;
    calculateProjectionMatrix();
}

void Camera::setHeight(float height) {
    this->height = height;
    calculateProjectionMatrix();
}
