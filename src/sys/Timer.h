#pragma once

/**
 * @brief Declarations for timer operations.
 */
namespace timer {
    /**
     * @brief Initializes the timer system.
     */
    void init();

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
     * @return The time difference in milliseconds.
     */
    double getTimeDiff(unsigned int id);

    /**
     * @brief Stop the thread for a specific duration.
     * @param milliseconds duration in milliseconds.
     */
    void delay(double milliseconds);
}

namespace benchmark {
    /**
     * @brief Starts the benchmark timer.
     */
    void startBenchmark();

    /**
     * @brief Ends the benchmark timer
     */
    void endBenchmark();

    /**
     * Returns the duration of the last frame in seconds.
     *
     * @param precision The precision of the last frame duration. Defaults to 6.
     * @return The duration of the last frame in seconds.
     */
    double getLastFrameDuration(int precision = 6);

    /**
     * Retrieves the benchmark result.
     *
     * This function returns the benchmark result as a double value.
     *
     * @param precision The precision of the benchmark result. Defaults to 6.
     * @return The benchmark result as a double value.
     */
    double getBenchmarkResult(int precision = 6);

    /**
     * @brief Counts the total number of frames and calculates the average frame time.
     */
    void countFrames();

    /**
     * @brief Returns the average frame time in milliseconds.
     * @return The average frame time in milliseconds.
     */
    double getAverageFrameTime(int precision = 6);
}