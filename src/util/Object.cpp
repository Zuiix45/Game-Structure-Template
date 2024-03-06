#include "Object.h"

#include "../sys/Logger.h"

#include "renderer/DefaultShaders.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Object::Object(float x, float y, float width, float height, float angle) 
            : x(x), y(y), width(width), height(height), angle(angle) {

    topLeftColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    topRightColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    bottomLeftColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);
    bottomRightColor = glm::vec4(255.0f, 255.0f, 255.0f, 1.0f);

    startTimerID = timer::createTimer();

    animationClosed = false;
    visible = true;

    indices = new int[6];
    vertices = new Vertex[4];

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    vertices[0] = {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)};
    vertices[1] = {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)};
    vertices[2] = {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)};
    vertices[3] = {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)};

    type = ObjectType::STATIC;
}

Object::~Object() {
    timer::killTimer(startTimerID);

    delete vertices;
    delete indices;
}

void Object::draw(int windowWidth, int windowHeight) {
    if (!visible) return;

    bool isAnimationStepUp = false;

    if (isAnimationValid() && !animationClosed) {
        animation.value()->step();
        isAnimationStepUp = false;
    }

    if (buffers.has_value() && shaders.has_value()) {
        shaders.value()->activate();
        glm::mat4 model = getModelMatrix(windowWidth, windowHeight);
        shaders.value()->setUniform("u_Model", (float*)&model, SHADER_MAT4);

        updateColorData();

        buffers.value()->bind();
        buffers.value()->setVertexData(vertices, indices);
        buffers.value()->drawElements();
        buffers.value()->unbind();
    }

    if (isAnimationStepUp) { animation.value()->deactivate(); }
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
            logError("Invalid corner specified", INVALID_CORNER_SPECIFIED);
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
            logError("Invalid corner specified", INVALID_CORNER_SPECIFIED);
            break;
    }
}

void Object::setAnimation(std::vector<std::string> paths, int fps, double speed, bool flip) {
    animation = std::make_unique<Animation>(paths, fps, speed, flip);
}

bool Object::isAnimationValid() {
    if (animation == nullptr) return false;
    if (!animation.has_value()) return false;
    if (animation.value()->isLoadedSuccessfully()) return true;
    
    return false;
}

void Object::closeAnimation() { animationClosed = true; }
void Object::openAnimation() { animationClosed = false; }

void Object::setBuffers(std::shared_ptr<Buffers> mBuffers) {
    buffers = mBuffers;
}

void Object::setShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
    shaders = std::make_shared<Shaders>(vertexShaderSource, fragmentShaderSource);
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

void Object::updateColorData() {
    glm::vec4 normalizedTopLeftColor = glm::vec4(topLeftColor.r/255.0f, topLeftColor.g/255.0f, topLeftColor.b/255.0f, topLeftColor.a);
    glm::vec4 normalizedTopRightColor = glm::vec4(topRightColor.r/255.0f, topRightColor.g/255.0f, topRightColor.b/255.0f, topRightColor.a);
    glm::vec4 normalizedBottomLeftColor = glm::vec4(bottomLeftColor.r/255.0f, bottomLeftColor.g/255.0f, bottomLeftColor.b/255.0f, bottomLeftColor.a);
    glm::vec4 normalizedBottomRightColor = glm::vec4(bottomRightColor.r/255.0f, bottomRightColor.g/255.0f, bottomRightColor.b/255.0f, bottomRightColor.a);

    vertices[0].color = normalizedTopLeftColor;
    vertices[1].color = normalizedTopRightColor;
    vertices[2].color = normalizedBottomRightColor;
    vertices[3].color = normalizedBottomLeftColor;
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

ObjectType Object::getType() const {
    return type;
}