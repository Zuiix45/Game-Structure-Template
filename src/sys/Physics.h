#pragma once

#include "../util/Object.h"

namespace physics {
    bool isColliding(unsigned int objectID1, unsigned int objectID2);
    void loop();
}