#include "Barrier.h"

#include "../sys/Handler.h"

Barrier::Barrier(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;

    this->width = width;
    this->height = height;

    setColor(0, 0, 0);
}