#pragma once

#include "../headers.h"

class NonEntity : public Object {
public:
    NonEntity();

    virtual void events() = 0; // override this function to handle events
};