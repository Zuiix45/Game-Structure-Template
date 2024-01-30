#include "Physics.h"

bool physics::isColliding(float hitbox1[4], float hitbox2[4]) {
    if (hitbox1[0] < hitbox2[0] + hitbox2[2] &&
        hitbox1[0] + hitbox1[2] > hitbox2[0] &&
        hitbox1[1] < hitbox2[1] + hitbox2[3] &&
        hitbox1[1] + hitbox1[3] > hitbox2[1]) {
        return true;
    }

    return false;
}
