#pragma once

#include "../util/Object.h"

/**
 * @brief This class represents a non-entity objects. 
 * Non-entity objects are objects that are not affected by physics.
 * However, they are in-game objects that's why they are affected by the camera.
 * 
 */
class NonEntity : public Object {
public:
    NonEntity();

    virtual void events() {}; // override this function to handle events
};