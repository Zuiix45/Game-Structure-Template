#pragma once

#include "../util/Object.h"

class Player : public Object {
public:
    Player();

    void update(float deltaTime);
    void events();
private:
    char moveUpKey;
    char moveDownKey;
    char moveLeftKey;
    char moveRightKey;

    float vX;
    float vY;

    Animation* lookUp;
    Animation* lookDown;
    Animation* lookLeft;
    Animation* lookRight;

    float baseSpeed;

    void controlMovement();
};