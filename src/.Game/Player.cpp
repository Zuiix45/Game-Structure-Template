#include "Player.h"

Player::Player(float x, float y, float width, float height, float baseSpeed) : baseSpeed(baseSpeed) {
    keyLeft = KEY_LEFT;
    keyRight = KEY_RIGHT;

    setX(x);
    setY(y);
    setWidth(width);
    setHeight(height);

    ////////////

    SpriteList spritesStand;

    spritesStand.push_back("playerstand_0_0");
    spritesStand.push_back("playerstand_0_1");
    spritesStand.push_back("playerstand_0_2");

    animStand = make<Animation>(6, 1);
    animStand->loadKeyFrames(spritesStand, false);
    animStand->loop();

    ////////

    SpriteList spritesWalk;

    spritesWalk.push_back("playerwalk_0_0");
    spritesWalk.push_back("playerwalk_0_1");
    spritesWalk.push_back("playerwalk_0_2");

    animWalk = make<Animation>(6, 1);
    animWalk->loadKeyFrames(spritesWalk, false);
    animWalk->loop();

    /////////

    SpriteList spritesStartJump;

    spritesStartJump.push_back("playerstartjump_0_0");
    spritesStartJump.push_back("playerstartjump_0_1");
    spritesStartJump.push_back("playerstartjump_0_2");

    animStartJump = make<Animation>(6, 1);
    animStartJump->loadKeyFrames(spritesStartJump, false);

    ////////

    setAnimation(animStand);

    ////////

    setAccelerationY(physics::getGravity());
}

void Player::update(double elapsedTime) {
    physics::accelerate(getID(), elapsedTime);
    physics::move(getID(), elapsedTime);

    if (y > 250) {
        y = 250; // ground level
        setVelocityY(0);
        isJumping = false;
    }
}

void Player::events() {
    if (input::isPressedOrHeld(keyLeft) && !isJumping) {
        // player moves lefts
        setVelocityX(-baseSpeed);
        setAnimation(animWalk);
        resetHorizontalFlip();
    }

    if (input::isPressedOrHeld(keyRight) && !isJumping) {
        // player moves right
        setVelocityX(baseSpeed);
        setAnimation(animWalk);
        flipHorizontal();
    }

    if (input::isKeyReleased(keyLeft) && input::isKeyReleased(keyRight) && !isJumping) {
        // if no keys are pressed, player stops
        setVelocityX(0);
        setAnimation(animStand);
    }

    if (input::isPressedOrHeld(keyLeft) && input::isPressedOrHeld(keyRight) && !isJumping) {
        // if both keys are pressed, player stops
        setVelocityX(0);
        setAnimation(animStand);
    }

    if (input::isKeyPressed(KEY_SPACE) && !isJumping) {
        // player jumps
        setVelocityY(-baseSpeed);
        setAnimation(animStartJump);

        isJumping = true;

        hMax = baseSpeed * baseSpeed / (2 * physics::getGravity()); // no more required
    }
}