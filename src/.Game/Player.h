#pragma once

#include "../headers.h"

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
    float jumpSpeed;

    float middleAreaX, middleAreaY;
    float middleAreaWidth, middleAreaHeight;

    bool isJumping = false;

    bool isCamFree = false; // true if player is in the middle of the screen

    float hMax;
};