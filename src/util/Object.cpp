#include "Object.h"

#include "../sys/Logger.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Object::Object(float x, float y, float width, float height, float angle) 
            : x(x), y(y), width(width), height(height), angle(angle) {

    topLeftcolor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    topRightcolor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    bottomLeftcolor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    bottomRightcolor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
}

float Object::getX() const { return x; }
float Object::getY() const { return y; }
float Object::getWidth() const { return width; }
float Object::getHeight() const { return height; }
float Object::getAngle() const { return angle; }

glm::vec4 Object::getColor(unsigned int corner) const {
    switch (corner) {
        case TOP_LEFT_CORNER:
            return topLeftcolor;
            break;
        case TOP_RIGHT_CORNER:
            return topRightcolor;
            break;
        case BOTTOM_LEFT_CORNER:
            return bottomLeftcolor;
            break;
        case BOTTOM_RIGHT_CORNER:
            return bottomRightcolor;
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
            topLeftcolor = glm::vec4(r, g, b, a);
            break;
        case TOP_RIGHT_CORNER:
            topRightcolor = glm::vec4(r, g, b, a);
            break;
        case BOTTOM_LEFT_CORNER:
            bottomLeftcolor = glm::vec4(r, g, b, a);
            break;
        case BOTTOM_RIGHT_CORNER:
            bottomRightcolor = glm::vec4(r, g, b, a);
            break;
        case ALL_CORNERS:
            topLeftcolor = glm::vec4(r, g, b, a);
            topRightcolor = glm::vec4(r, g, b, a);
            bottomLeftcolor = glm::vec4(r, g, b, a);
            bottomRightcolor = glm::vec4(r, g, b, a);
            break;
        default:
            logError("Invalid corner specified", 0);
            break;
    }
}

void Object::setAnimation(Animation* animation) {
    if (animation->isLoadedSuccessfully())
        this->animation = animation;
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

    glm::vec4 normalizedTopLeftColor = glm::vec4(topLeftcolor.r/255.0f, topLeftcolor.g/255.0f, topLeftcolor.b/255.0f, topLeftcolor.a);
    glm::vec4 normalizedTopRightColor = glm::vec4(topRightcolor.r/255.0f, topRightcolor.g/255.0f, topRightcolor.b/255.0f, topRightcolor.a);
    glm::vec4 normalizedBottomLeftColor = glm::vec4(bottomLeftcolor.r/255.0f, bottomLeftcolor.g/255.0f, bottomLeftcolor.b/255.0f, bottomLeftcolor.a);
    glm::vec4 normalizedBottomRightColor = glm::vec4(bottomRightcolor.r/255.0f, bottomRightcolor.g/255.0f, bottomRightcolor.b/255.0f, bottomRightcolor.a);

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
