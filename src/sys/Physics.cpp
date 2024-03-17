#include "Physics.h"

#include "Engine.h"

#include "../classes/Entity.h"
#include "../util/Object.h"

namespace{
    float gravity = 0.0f;
}

bool physics::isColliding(unsigned int objectID1, unsigned int objectID2) {

    cast<Object> object1 = engine::getObject(objectID1);
    cast<Object> object2 = engine::getObject(objectID2);

    float x1 = object1->getX();
    float y1 = object1->getY();
    float width1 = object1->getWidth();
    float height1 = object1->getHeight();

    float x2 = object2->getX();
    float y2 = object2->getY();
    float width2 = object2->getWidth();
    float height2 = object2->getHeight();

    if (x1 < x2 + width2 &&
        x1 + width1 > x2 &&
        y1 < y2 + height2 &&
        y1 + height1 > y2) return true;

    return false;
}

void physics::move(unsigned int entityID, double elapsedTime) {
    cast<Entity> entity = std::dynamic_pointer_cast<Entity>(engine::getObject(entityID));

    entity->setX(entity->getX() + entity->getVelocityX() * elapsedTime);
    entity->setY(entity->getY() + entity->getVelocityY() * elapsedTime);
}

void physics::moveWithAngle(unsigned int entityID, double elapsedTime, float baseSpeed) {
    cast<Entity> entity = std::dynamic_pointer_cast<Entity>(engine::getObject(entityID));

    entity->setVelocityX(baseSpeed * cos(entity->getAngle()));
    entity->setVelocityY(baseSpeed * sin(entity->getAngle()));

    move(entityID, elapsedTime);
}

void physics::accelerate(unsigned int entityID, double elapsedTime) {
    cast<Entity> entity = std::dynamic_pointer_cast<Entity>(engine::getObject(entityID));

    entity->setVelocityX(entity->getVelocityX() + entity->getAccelerationX() * elapsedTime);
    entity->setVelocityY(entity->getVelocityY() + entity->getAccelerationY() * elapsedTime);
}

void physics::setGravity(float newGravity) { gravity = newGravity; }
float physics::getGravity() { return gravity; }
