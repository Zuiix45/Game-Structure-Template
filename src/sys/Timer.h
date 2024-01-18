#pragma once

/**
 * @brief Declarations for timer operations.
 */
namespace timer {
    /**
     * @brief Create a timer and return its ID.
     * @return The ID of the created timer.
     */
    unsigned int createTimer();

    /**
     * @brief Reset the timer associated with the given ID.
     * @param id The ID of the timer to be reset.
     */
    void resetTimer(unsigned int id);

    /**
     * @brief Kills the timer associated with the given ID.
     * @param id The ID of the timer to be reset.
     */
    void killTimer(unsigned int id);

    /**
     * @brief Get the time difference (in milliseconds) between the current time and the time associated with the given ID.
     * @param id The ID of the timer.
     * @return The time difference in seconds.
     */
    double getTimeDiff(unsigned int id);

    /**
     * @brief Stop the thread for a specific duration.
     * @param milliseconds duration in milliseconds.
     */
    void delay(double milliseconds);
}
