#include "Entity.h"

Entity::Entity() : Object(ObjectType::ENTITY) {
    _velocityX = 0;
    _velocityY = 0;
    _accelerationX = 0;
    _accelerationY = 0;
    _mass = 1;
    loopTimer = timer::createTimer();

    effectByCamera(true); // all entities are affected by camera
}

double Entity::getElapsedTime() {
    auto elapsedTime = timer::getTimeDiff(loopTimer);
    timer::resetTimer(loopTimer);
    return elapsedTime;
}

void Entity::setVelocityX(float velocityX) { _velocityX = velocityX; }
void Entity::setVelocityY(float velocityY) { _velocityY = velocityY; }
void Entity::setAccelerationX(float accelerationX) { _accelerationX = accelerationX; }
void Entity::setAccelerationY(float accelerationY) { _accelerationY = accelerationY; }
void Entity::setMass(float mass) { _mass = mass; }

float Entity::getVelocityX() { return _velocityX; }
float Entity::getVelocityY() { return _velocityY; }
float Entity::getAccelerationX() { return _accelerationX; }
float Entity::getAccelerationY() { return _accelerationY; }
float Entity::getMass() { return _mass; }
