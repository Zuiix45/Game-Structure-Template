#include "Physics.h"

#include "Engine.h"

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
