#include "Player.h"

#include "../sys/Handler.h"
#include "../sys/Physics.h"
#include "../sys/Logger.h"

#include "../util/Hitbox.h"

#include "Game.h"

Player::Player() {

    moveUpKey = 'w';
    moveDownKey = 's';
    moveLeftKey = 'a';
    moveRightKey = 'd';

    width = 128;
    height = 128;

    lookUp = new Animation(handler::getSprite("playerUp"));
    lookDown = new Animation(handler::getSprite("playerDown"));
    lookLeft = new Animation(handler::getSprite("playerLeft"));
    lookRight = new Animation(handler::getSprite("playerRight"));

    baseSpeed = 0.2f;

    setAnimation(lookDown);

    handler::createObject(PLAYER_LAYER, "player_hitbox", new Hitbox(this, 45, 30, 42, 82));
}

void Player::controlMovement() {
    if (input::isKeyDown(moveUpKey)) {
        vY = -baseSpeed;
        setAnimation(lookUp);
    }

    else if (input::isKeyDown(moveDownKey)) { 
        vY = baseSpeed;
        setAnimation(lookDown);
    }

    else vY = 0;

    if (input::isKeyDown(moveLeftKey)) { 
        vX = -baseSpeed;
        setAnimation(lookLeft);
    }

    else if (input::isKeyDown(moveRightKey)) { 
        vX = baseSpeed;
        setAnimation(lookRight);
    }

    else vX = 0;
}

void Player::update(float deltaTime) {
    x += vX * deltaTime;
    y += vY * deltaTime;

    if (physics::isColliding(obj("player_hitbox"), obj("barrier"))) {
        logInfo("Colliding with barrier");
    }
}

void Player::events() {
    controlMovement();
}