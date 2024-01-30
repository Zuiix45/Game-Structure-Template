#include "Hitbox.h"

#include "../sys/Handler.h"

Hitbox::Hitbox(Object* master, float xOffset, float yOffset, float width, float height, float angle) {
    this->master = master;

    this->xOffset = xOffset;
    this->yOffset = yOffset;

    this->x = master->getX() + xOffset;
    this->y = master->getY() + yOffset;

    this->width = width;
    this->height = height;

    this->angle = angle;

    setAnimation(new Animation(handler::getSprite("hitbox")));
}

void Hitbox::update(float deltaTime) {
    this->x = master->getX() + xOffset;
    this->y = master->getY() + yOffset;
}

void Hitbox::events() {
}
