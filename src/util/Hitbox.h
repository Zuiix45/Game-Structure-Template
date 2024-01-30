#pragma once

#include "Object.h"

class Hitbox : public Object {
public:
    Hitbox(Object* master, float xOffset, float yOffset, float width, float height, float angle = 0);

    void update(float deltaTime) override;
    void events() override;

private:
    Object* master;

    float xOffset;
    float yOffset;
};