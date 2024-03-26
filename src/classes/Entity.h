#pragma once

#include "../headers.h"

/**
 * @brief This class represents a entity objects.
 * Entity objects are objects that are affected by physics and camera.
 * They are the main objects that can be moved and interacted.
 * 
 */
class Entity : public Object {
public:
    Entity();

    virtual void update(double elapsedTime) = 0; // override this function to update object
    virtual void events() = 0; // override this function to handle events

    /**
     * @brief Returns the elapsed time since the last execution of this object in the last frame.
     * It is used for calculating elapsed time for "update" function.
     * WARNING: This function is called automatically per frame by the engine.
     * 
     * @return double elapsed time in milliseconds
     */
    double getFrameTime();

    void setVelocityX(float velocityX);
    void setVelocityY(float velocityY);
    void setAccelerationX(float accelerationX);
    void setAccelerationY(float accelerationY);
    void setMass(float mass);

    float getVelocityX();
    float getVelocityY();
    float getAccelerationX();
    float getAccelerationY();
    float getMass();

private:
    float _velocityX, _velocityY; // m/s
    float _accelerationX, _accelerationY; // m/s^2
    float _mass; // kg

    unsigned int loopTimer;
};