#pragma once

namespace physics {
    /**
    * @brief Checks if two hitboxes are colliding.
    *
    * @param hitbox1 The first hitbox represented by an array of 4 floats.
    * @param hitbox2 The second hitbox represented by an array of 4 floats.
    * @return True if the hitboxes are colliding, false otherwise.
    */
    bool isColliding(float hitbox1[4], float hitbox2[4]);
}