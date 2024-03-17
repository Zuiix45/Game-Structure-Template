#pragma once

#include "../headers.h"

class Entity : public Object {
public:
    Entity();

    virtual void update(double elapsedTime) = 0; // override this function to update object
    virtual void events() = 0; // override this function to handle events

    double getElapsedTime();

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