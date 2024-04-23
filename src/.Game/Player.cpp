#include "Player.h"

#include "../core/Application.h"

Player::Player(float x, float y, float width, float height, float baseSpeed) : baseSpeed(baseSpeed) {
    keyLeft = KEY_LEFT;
    keyRight = KEY_RIGHT;

    setX(x);
    setY(y);
    setWidth(width);
    setHeight(height);

    jumpSpeed = baseSpeed * 2;

    hMax = 0;

    ////////////

    SpriteList spritesStand;

    spritesStand.push_back("playerstand_0_0");
    spritesStand.push_back("playerstand_0_1");
    spritesStand.push_back("playerstand_0_2");

    animStand = make<Animation>(6, 1); // fps, speed
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

    ///////
}

void Player::update(double elapsedTime) {
    physics::accelerate(getID(), elapsedTime);
    physics::move(getID(), elapsedTime);

    float groundLevel = obj("ground")->getY();

    if (y > groundLevel - height) {
        y = groundLevel - height; // ground level
        setVelocityY(0);
        isJumping = false;
    }

    text::setRendererX(500);
    text::setRendererY(50);
    text::setRendererScale(0.5f);
    text::renderText(DEF_FONT, "Player X: " + std::to_string(x) + " Ground X: " + std::to_string(obj("ground")->getX()));
}

void Player::events() {
    if (input::isPressedOrHeld(keyLeft) && !isJumping) {
        // player moves left
        setVelocityX(-baseSpeed);
        setAnimation(animWalk);
        flipHorizontal();
    }

    if (input::isPressedOrHeld(keyRight) && !isJumping) {
        // player moves right
        setVelocityX(baseSpeed);
        setAnimation(animWalk);
        resetHorizontalFlip();
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