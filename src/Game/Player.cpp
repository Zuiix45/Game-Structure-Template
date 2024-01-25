#include "Player.h"

#include "../sys/Handler.h"

Player::Player() {

    moveUpKey = 'w';
    moveDownKey = 's';
    moveLeftKey = 'a';
    moveRightKey = 'd';

    width = 128;
    height = 128;
}

void Player::update(float deltaTime) {
    x += vX * deltaTime;
    y += vY * deltaTime;
}

void Player::events() {
    if (input::isKeyDown(moveUpKey)) {
        vY = -1;
        setAnimation(new Animation(handler::getSprite("playerUp")));
    }

    if (input::isKeyDown(moveDownKey)) { 
        vY = 1;
        setAnimation(new Animation(handler::getSprite("playerDown")));
    }

    if (input::isKeyDown(moveLeftKey)) { 
        vX = -1;
        setAnimation(new Animation(handler::getSprite("playerLeft")));
    }

    if (input::isKeyDown(moveRightKey)) { 
        vX = 1;
        setAnimation(new Animation(handler::getSprite("playerRight")));
    }

    else {
        vX = 0;
        vY = 0;
    }
}