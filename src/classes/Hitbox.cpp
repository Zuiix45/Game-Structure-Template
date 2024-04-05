#include "Hitbox.h"

#include "../sys/Engine.h"
#include "../sys/Events.h"

#include "../core/Application.h"

Hitbox::Hitbox(unsigned int parentID, float relativeX, float relativeY, float width, float height, float angle) 
    : _parentID(parentID), Object(ObjectType::HITBOX, relativeX, relativeY, width, height, angle) {

    _relativeX = relativeX;
    _relativeY = relativeY;

    showKeyCode = GLFW_KEY_F3;

    setBuffers(engine::getBuffers(EMPTY_RECTANGULAR_BUFFERS));

    closeAnimation();

    createVertexData();
    createIndexData();
}

void Hitbox::draw(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) {
    if (!App::isShowingStats()) return;

    if (buffers.has_value() && shaders.has_value()) {
        shaders.value()->activate();
        glm::mat4 model = getModelMatrix(window->getWidth(), window->getHeight());
        glm::mat4 view = window->getProjectionMatrix();
        shaders.value()->setUniform("u_Model", (float*)&model, SHADER_MAT4);
        shaders.value()->setUniform("u_View", (float*)&view, SHADER_MAT4);

        if (isAffectedByCamera() && camera != nullptr) {
            glm::mat4 view = camera->getViewMatrix();
            glm::mat4 projection = camera->getProjectionMatrix();
            shaders.value()->setUniform("u_View", (float*)&view, SHADER_MAT4);
            shaders.value()->setUniform("u_Projection", (float*)&projection, SHADER_MAT4);
        }

        buffers.value()->bind();
        buffers.value()->setVertexData(vertices, indices);
        buffers.value()->drawElements(GL_LINES);
        buffers.value()->unbind();
    }
}

void Hitbox::syncCoordsWithParent() {
    setX(engine::getObject(_parentID)->getX() + _relativeX);
    setY(engine::getObject(_parentID)->getY() + _relativeY);
}

void Hitbox::syncAngleWithParent() {
    setRotation(engine::getObject(_parentID)->getAngle());
}

void Hitbox::createVertexData() {
    if (vertices.size() > 0) vertices.clear();

    vertices.push_back({glm::vec3(-WINDOW_WIDTH/4.0f, -WINDOW_HEIGHT/4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)});
    vertices.push_back({glm::vec3(WINDOW_WIDTH/4.0f, -WINDOW_HEIGHT/4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)});
    vertices.push_back({glm::vec3(WINDOW_WIDTH/4.0f, WINDOW_HEIGHT/4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)});
    vertices.push_back({glm::vec3(-WINDOW_WIDTH/4.0f, WINDOW_HEIGHT/4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)});
}

void Hitbox::createIndexData() {
    if (indices.size() > 0) indices.clear();

    indices.push_back(0);
    indices.push_back(2);

    indices.push_back(2);
    indices.push_back(1);

    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(3);
    indices.push_back(0);
}
