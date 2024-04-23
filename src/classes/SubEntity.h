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

    virtual void update(double elapsedTime) {}; // override this function to update object
    virtual void events() {}; // override this function to handle events

    /**
     * @brief Returns the elapsed time since the last execution of this object in the last frame.
     * It is used for calculating elapsed time for "update" function.
     * WARNING: This function is called automatically per frame by the engine.
     * 
     * @return double elapsed time in milliseconds
     */
    double getFrameTime();

private:
    unsigned int loopTimer;
};
