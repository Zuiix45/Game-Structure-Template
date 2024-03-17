#pragma once

#include "../classes/Entity.h"

class Player : public Entity {
public:
    Player(float x, float y, float width, float height, float baseSpeed);

    void update(double elapsedTime) override;
    void events() override;

private:
    Key keyLeft;
    Key keyRight;

    cast<Animation> animWalk;
    cast<Animation> animStand;
    cast<Animation> animStartJump;

    float baseSpeed;

    bool isJumping = false;

    float hMax;
};