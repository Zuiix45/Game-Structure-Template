#pragma once

#include "../util/Object.h"

class SubEntity : public Object {
public:
    SubEntity();

    virtual void update(double elapsedTime) = 0; // override this function to update object
    virtual void events() = 0; // override this function to handle events

    double getElapsedTime();

private:
    unsigned int loopTimer;
};
