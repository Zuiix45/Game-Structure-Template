#include "Object.h"

#include "../sys/Logger.h"

#include "gl/DefaultShaders.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Object::Object(float x, float y, float width, float height, float angle) 
            : x(x), y(y), width(width), height(height), angle(angle) {

    topLeftColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    topRightColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    bottomLeftColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    bottomRightColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);

    startTimerID = timer::createTimer();

    animation = nullptr;
}

float Object::getX() const { return x; }
float Object::getY() const { return y; }
float Object::getWidth() const { return width; }
float Object::getHeight() const { return height; }
float Object::getAngle() const { return angle; }

float* Object::getBounds() const {
    float* bounds = new float[4];

    bounds[0] = x;
    bounds[1] = y;
    bounds[2] = width;
    bounds[3] = height;

    return bounds;
}

glm::vec4 Object::getColor(unsigned int corner) const {
    switch (corner) {
        case TOP_LEFT_CORNER:
            return topLeftColor;
            break;
        case TOP_RIGHT_CORNER:
            return topRightColor;
            break;
        case BOTTOM_LEFT_CORNER:
            return bottomLeftColor;
            break;
        case BOTTOM_RIGHT_CORNER:
            return bottomRightColor;
            break;
        default:
            logError("Invalid corner specified", 0);
            return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            break;
    }
}

void Object::setX(float x) { this->x = x; }
void Object::setY(float y) { this->y = y; }
void Object::setRotation(float angle) { this->angle = angle; }
void Object::setWidth(float width) { this->width = width; }
void Object::setHeight(float height) { this->height = height; }

void Object::setColor(float r, float g, float b, float a, unsigned int corner) {
    switch (corner) {
        case TOP_LEFT_CORNER:
            topLeftColor = glm::vec4(r, g, b, a);
            break;
        case TOP_RIGHT_CORNER:
            topRightColor = glm::vec4(r, g, b, a);
            break;
        case BOTTOM_LEFT_CORNER:
            bottomLeftColor = glm::vec4(r, g, b, a);
            break;
        case BOTTOM_RIGHT_CORNER:
            bottomRightColor = glm::vec4(r, g, b, a);
            break;
        case ALL_CORNERS:
            topLeftColor = glm::vec4(r, g, b, a);
            topRightColor = glm::vec4(r, g, b, a);
            bottomLeftColor = glm::vec4(r, g, b, a);
            bottomRightColor = glm::vec4(r, g, b, a);
            break;
        default:
            logError("Invalid corner specified", 0);
            break;
    }
}

Animation* Object::setAnimation(Animation* animation) {
    if (animation->isLoadedSuccessfully()) {
        Animation* temp = this->animation;
        this->animation = animation;

        return temp;
    }

    return this->animation;
}

Animation* Object::getAnimation() const {
    return animation;
}

glm::mat4 Object::getModelMatrix(int windowWidth, int windowHeight) const {
    // Normalize Values
    float normalizedX = (x * 2 + width - windowWidth) / windowWidth;
    float normalizedY = (-y * 2 - height + windowHeight) / windowHeight;
    float normalizedScaleX = width / (windowWidth/2.0f);
    float normalizedScaleY = height / (windowHeight/2.0f);

    // Create Transformation Matrix
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(normalizedX, normalizedY, 1.0f));
    model = glm::scale(model, glm::vec3(normalizedScaleX, normalizedScaleY, 1.0f));
    model = glm::rotate(model, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));

    return model;
}

std::vector<Vertex> Object::getVertices() const {
    std::vector<Vertex> vertices;

    glm::vec4 normalizedTopLeftColor = glm::vec4(topLeftColor.r/255.0f, topLeftColor.g/255.0f, topLeftColor.b/255.0f, topLeftColor.a);
    glm::vec4 normalizedTopRightColor = glm::vec4(topRightColor.r/255.0f, topRightColor.g/255.0f, topRightColor.b/255.0f, topRightColor.a);
    glm::vec4 normalizedBottomLeftColor = glm::vec4(bottomLeftColor.r/255.0f, bottomLeftColor.g/255.0f, bottomLeftColor.b/255.0f, bottomLeftColor.a);
    glm::vec4 normalizedBottomRightColor = glm::vec4(bottomRightColor.r/255.0f, bottomRightColor.g/255.0f, bottomRightColor.b/255.0f, bottomRightColor.a);

    vertices.push_back({glm::vec3(-0.5f, -0.5f, 0.0f), normalizedTopLeftColor, glm::vec2(0.0f, 0.0f)});
    vertices.push_back({glm::vec3(0.5f, -0.5f, 0.0f), normalizedTopRightColor, glm::vec2(1.0f, 0.0f)});
    vertices.push_back({glm::vec3(0.5f, 0.5f, 0.0f), normalizedBottomLeftColor, glm::vec2(1.0f, 1.0f)});
    vertices.push_back({glm::vec3(-0.5f, 0.5f, 0.0f), normalizedBottomRightColor, glm::vec2(0.0f, 1.0f)});

    return vertices;
}

std::vector<unsigned int> Object::getIndices() const {
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    return indices;
}

void Object::show() {
    visible = true;
}

void Object::hide() {
    visible = false;
}

bool Object::isVisible() const {
    return visible;
}
