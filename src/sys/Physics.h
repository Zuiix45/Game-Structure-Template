#pragma once

namespace physics {
    /**
     * @brief Creates a hit box with the specified bounds.
     * 
     * @param bounds An array of four floats representing the bounds of the hit box.
     *               The order of the values should be [left, top, right, bottom].
     * 
     * @return An unsigned integer representing the ID of the created hit box.
     */
    unsigned int createHitBox(float bounds[4]);

    /**
     * Listens for collisions between two hit boxes.
     *
     * @param hitBox1 The ID of the first hit box.
     * @param hitBox2 The ID of the second hit box.
     * @return The number of collisions detected.
     */
    unsigned int listenCollisions(unsigned int hitBox1, unsigned int hitBox2);

    /**
     * @brief Checks for collisions between objects.
     * 
     * This function is responsible for detecting collisions between objects in the system.
     * It performs collision detection algorithms and updates the state of the objects accordingly.
     * 
     * @note This function does not handle collision resolution. It only detects collisions and updates object states.
     */
    void checkCollisions();

    /**
     * Checks if the object is colliding with the specified collision.
     *
     * @param collision The collision to check against.
     * @return True if the object is colliding with the collision, false otherwise.
     */
    bool isColliding(unsigned int collision);

    /**
     * @brief Destroys a hitBox.
     *
     * This function destroys the hitBox identified by the given hitBox ID.
     *
     * @param hitBox The ID of the hitBox to be destroyed.
     */
    void destroyHitBox(unsigned int hitBox);
}