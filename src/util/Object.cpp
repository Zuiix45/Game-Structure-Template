#include "Object.h"

#include "../sys/Logger.h"
#include "../sys/Engine.h"

#include "../core/Application.h"

#include "renderer/DefaultShaders.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Object::Object(ObjectType type, float x, float y, float width, float height, float angle) 
            : type(type), x(x), y(y), width(width), height(height), angle(angle) {

    createVertexData();
    createIndexData();

    startTimerID = timer::createTimer();

    animationClosed = false;
    visible = true;
    affectedByCamera = false;
    isAnimationFlippedHorizontal = false;
    isAnimationFlippedVertical = false;

    setBuffers(engine::getBuffers(RECTANGULAR_BUFFERS));
    setShaders(defaultVertexShaderSource, defaultFragmentShaderSource);
}

Object::~Object() {
    timer::killTimer(startTimerID);
}

void Object::draw(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) {
    if (!visible) return;

    bool isAnimationStepUp = false;

    if (isAnimationValid() && !animationClosed) {
        animation.value()->step();
        isAnimationStepUp = true;
    }

    if (buffers.has_value() && shaders.has_value()) {
        // prepare shaders for drawing
        shaders.value()->activate();
        glm::mat4 model = getModelMatrix(window->getWidth(), window->getHeight());
        glm::mat4 view = window->getProjectionMatrix();
        shaders.value()->setUniform("u_Model", (float*)&model, SHADER_MAT4);
        shaders.value()->setUniform("u_View", (float*)&view, SHADER_MAT4);

        if (affectedByCamera) {
            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 projection = camera->getProjectionMatrix();
            shaders.value()->setUniform("u_View", (float*)&view, SHADER_MAT4);
            shaders.value()->setUniform("u_Projection", (float*)&projection, SHADER_MAT4);
        }

        // pass data to vram and draw
        buffers.value()->bind();
        buffers.value()->setVertexData(vertices, indices);
        buffers.value()->drawElements(GL_TRIANGLES);
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

glm::vec4 Object::getColor(unsigned int vertexIndex) const {
    return vertices.at(vertexIndex).color;
}

void Object::setX(float x) { this->x = x; }
void Object::setY(float y) { this->y = y; }
void Object::setRotation(float angle) { this->angle = angle; }
void Object::setWidth(float width) { this->width = width; }
void Object::setHeight(float height) { this->height = height; }

void Object::scale(float factor) {
    width *= factor;
    height *= factor;
}

void Object::setColor(float r, float g, float b, float a, unsigned int vertexIndex) {
    vertices.at(vertexIndex).color = glm::vec4(r/255.0f, g/255.0f, b/255.0f, a);
}

void Object::setAllColors(float r, float g, float b, float a) {
    for (int i = 0; i < vertices.size(); i++) {
        setColor(r, g, b, a, i);
    }
}

void Object::loadAnimation(std::vector<std::string> paths, int fps, double speed, bool flip) {
    animation = std::make_unique<Animation>(fps, speed);
    animation.value()->loadKeyFrames(paths, flip);
}

void Object::createAnimation(std::vector<unsigned int> keyframes, int fps, double speed) {
    animation = std::make_unique<Animation>(fps, speed);
    animation.value()->setKeyFrames(keyframes);
}

void Object::setAnimation(std::shared_ptr<Animation> newAnimation) {
    animation.emplace(newAnimation);
}

bool Object::isAnimationValid() {
    if (animation == nullptr) return false;
    if (!animation.has_value()) return false;
    if (animation.value()->isLoadedSuccessfully()) return true;
    
    return false;
}

void Object::closeAnimation(bool loadDefaultShaders) {
    animationClosed = true;

    if (loadDefaultShaders) {
        auto vertexShader = affectedByCamera ? defaultCameraVertexShaderSource : defaultVertexShaderSource;
        auto fragmentShader = animationClosed ? defaultNoTextureFragmentShaderSource : defaultFragmentShaderSource;

        setShaders(vertexShader, fragmentShader);
    }
}

void Object::openAnimation(bool loadDefaultShaders) {
    animationClosed = false;

    if (loadDefaultShaders) {
        auto vertexShader = affectedByCamera ? defaultCameraVertexShaderSource : defaultVertexShaderSource;
        auto fragmentShader = animationClosed ? defaultNoTextureFragmentShaderSource : defaultFragmentShaderSource;

        setShaders(vertexShader, fragmentShader);
    }
}

void Object::flipVertical() {
    if (!isAnimationFlippedVertical) {
        for (int i = 0; i < vertices.size(); i++) {
            vertices.at(i).texCoord.y = 1.0f - vertices.at(i).texCoord.y;
        }

        isAnimationFlippedVertical = true;
    }
}

void Object::flipHorizontal() {
    if (!isAnimationFlippedHorizontal) {
        for (int i = 0; i < vertices.size(); i++) {
            vertices.at(i).texCoord.x = 1.0f - vertices.at(i).texCoord.x;
        }

        isAnimationFlippedHorizontal = true;
    }
}

void Object::resetVerticalFlip() {
    if (isAnimationFlippedVertical) {
        for (int i = 0; i < vertices.size(); i++) {
            vertices.at(i).texCoord.y = 1.0f - vertices.at(i).texCoord.y;
        }

        isAnimationFlippedVertical = false;
    }
}

void Object::resetHorizontalFlip() {
    if (isAnimationFlippedHorizontal) {
        for (int i = 0; i < vertices.size(); i++) {
            vertices.at(i).texCoord.x = 1.0f - vertices.at(i).texCoord.x;
        }

        isAnimationFlippedHorizontal = false;
    }
}

void Object::setBuffers(std::shared_ptr<Buffers> mBuffers) {
    buffers = mBuffers;
}

void Object::setShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
    shaders = std::make_shared<Shaders>(vertexShaderSource, fragmentShaderSource);
}

glm::mat4 Object::getModelMatrix(int windowWidth, int windowHeight) const {
    // Create Transformation Matrix
    float scaleX = width / (windowWidth/2.0f);
    float scaleY = height / (windowHeight/2.0f);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(x + width/2.0f, y + height/2.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));
    model = glm::rotate(model, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));

    return model;
}

void Object::createVertexData() {
    // vertex position, color, texture coordinates
    vertices.push_back({glm::vec3(-WINDOW_WIDTH/4.0f, -WINDOW_HEIGHT/4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)});
    vertices.push_back({glm::vec3(WINDOW_WIDTH/4.0f, -WINDOW_HEIGHT/4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
    vertices.push_back({glm::vec3(WINDOW_WIDTH/4.0f, WINDOW_HEIGHT/4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
    vertices.push_back({glm::vec3(-WINDOW_WIDTH/4.0f, WINDOW_HEIGHT/4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)});
}

void Object::createIndexData() {
    //tell openGL how to connect vertices
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
}

void Object::effectByCamera(bool effect) {
    affectedByCamera = effect;

    auto vertexShader = affectedByCamera ? defaultCameraVertexShaderSource : defaultVertexShaderSource;
    auto fragmentShader = animationClosed ? defaultNoTextureFragmentShaderSource : defaultFragmentShaderSource;

    setShaders(vertexShader, fragmentShader);
}

void Object::setVisibility(bool newVisibility) { visible = newVisibility; }
void Object::setID(unsigned int newID) { id = newID; }
bool Object::isVisible() const { return visible; }
bool Object::isAffectedByCamera() const { return affectedByCamera; }
ObjectType Object::getType() const { return type; }
unsigned int Object::getID() const { return id; }