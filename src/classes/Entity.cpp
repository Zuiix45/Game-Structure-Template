#include "Entity.h"

Entity::Entity(double mass) {
    _velocityX = 0;
    _velocityY = 0;
    _accelerationX = 0;
    _accelerationY = 0;
    _mass = mass;
    type = ObjectType::ENTITY;
}

void Entity::update(double elapsedTime) {
    _velocityX += _accelerationX * elapsedTime;
    _velocityY += _accelerationY * elapsedTime;
    x += _velocityX * elapsedTime;
    y += _velocityY * elapsedTime;
}

void Entity::setVelocityX(double velocityX) { _velocityX = velocityX; }
void Entity::setVelocityY(double velocityY) { _velocityY = velocityY; }
void Entity::setAccelerationX(double accelerationX) { _accelerationX = accelerationX; }
void Entity::setAccelerationY(double accelerationY) { _accelerationY = accelerationY; }
void Entity::setMass(double mass) { _mass = mass; }

double Entity::getVelocityX() { return _velocityX; }
double Entity::getVelocityY() { return _velocityY; }
double Entity::getAccelerationX() { return _accelerationX; }
double Entity::getAccelerationY() { return _accelerationY; }
double Entity::getMass() { return _mass; }
