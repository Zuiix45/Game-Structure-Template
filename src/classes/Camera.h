#pragma once

#include <glm/glm.hpp>

class Camera {
    public:
        Camera(float x, float y, float width, float height, float zoom = 1.0f);

        void follow(unsigned int objectID);

        void setX(float x);
        void setY(float y);
        void setXOffset(float xOffset);
        void setYOffset(float yOffset);
        void setZoom(float zoom);
        void setWidth(float width);
        void setHeight(float height);

        void calculateViewMatrix();
        void calculateProjectionMatrix();

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

    private:
        float x, y;
        float xOffset, yOffset;
        float width, height;
        float zoom;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
};
