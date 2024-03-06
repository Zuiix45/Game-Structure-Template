#pragma once

#include "../util/Object.h"

class Entity : public Object {
public:
    Entity(double mass);

    void update(double elapsedTime);
    void setVelocityX(double velocityX);
    void setVelocityY(double velocityY);
    void setAccelerationX(double accelerationX);
    void setAccelerationY(double accelerationY);
    void setMass(double mass);

    double getVelocityX();
    double getVelocityY();
    double getAccelerationX();
    double getAccelerationY();
    double getMass();

private:
    double _velocityX, _velocityY; // m/s
    double _accelerationX, _accelerationY; // m/s^2
    double _mass; // kg
};