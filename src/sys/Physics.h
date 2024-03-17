#pragma once

namespace physics {
    bool isColliding(unsigned int objectID1, unsigned int objectID2);

    void move(unsigned int entityID, double elapsedTime);
    void moveWithAngle(unsigned int entityID, double elapsedTime, float baseSpeed);

    void accelerate(unsigned int entityID, double elapsedTime);

    void setGravity(float newGravity);

    float getGravity();
}