#pragma once

#include <glm/glm.hpp>

class Camera {
    public:
        Camera(float x, float y, float width, float height, float zoom = 1.0f);
        
        void follow(unsigned int objectID);

        void calculateViewMatrix();
        void calculateProjectionMatrix();

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

        void setX(float x);
        void setY(float y);
        void setXOffset(float xOffset);
        void setYOffset(float yOffset);
        void setZoom(float zoom);
        void setWidth(float width);
        void setHeight(float height);

        float getX();
        float getY();
        float getXOffset();
        float getYOffset();
        float getZoom();
        float getWidth();
        float getHeight();

    private:
        float x, y;
        float xOffset, yOffset;
        float width, height;
        float zoom;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
};
