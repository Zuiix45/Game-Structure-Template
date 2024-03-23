#pragma once

#include "../util/Object.h"

/**
 * @brief This class represents a sub-entity objects.
 * Sub-entity objects are objects that cannot be moved but can be interacted.
 * They are affected not affected by physics but affected by the camera.
 */
class SubEntity : public Object {
public:
    SubEntity();

    virtual void update(double elapsedTime) = 0; // override this function to update object
    virtual void events() = 0; // override this function to handle events

    double getElapsedTime();

private:
    unsigned int loopTimer;
};
