#pragma once

#include <vector>
#include <string>

/**
 * @brief The Animation class represents a sequence of frames that can be played back at a specific speed.
 */
class Animation {
public:
    /**
     * @brief Constructs an Animation object with the specified frames per second and speed.
     * @param fps The frames per second of the animation.
     * @param speed The speed of the animation.
     */
    Animation(int fps = 24, float speed = 1.0f);

    /**
     * @brief Destroys the Animation object.
     */
    ~Animation();

    /**
     * @brief Calculates the frame time based on the frames per second and speed.
     * Use this method to change speed or fps of animation.
     * @param fps The frames per second of the animation.
     * @param speed The speed of the animation.
     */
    void calculateFrameTime(int fps, float speed);

    /**
     * @brief Sets the keyframes of the animation.
     * @param newKeyframes The vector of keyframe indices.
     */
    void setKeyFrames(std::vector<unsigned int> newKeyframes);

    /**
     * @brief Loads the keyframes of the animation from sprite names.
     * @param spriteNames The vector of sprite names.
     * @param flip Indicates whether to flip the sprites horizontally.
     */
    void loadKeyFrames(std::vector<std::string> spriteNames, bool flip = true);

    /**
     * @brief Advances the animation by one frame.
     */
    void step();

    /**
     * @brief Deactivates the animation.
     */
    void deactivate();

    /**
     * @brief Starts looping the animation.
     */
    void loop();

    /**
     * @brief Stops the animation.
     */
    void stop();

    /**
     * @brief Resets the animation to its initial state.
     */
    void reset();

    /**
     * @brief Checks if the animation is currently looping.
     * @return True if the animation is looping, false otherwise.
     */
    bool isLooping() const;

    /**
     * @brief Checks if the animation has finished playing.
     * @return True if the animation has finished, false otherwise.
     */
    bool isFinished() const;

    /**
     * @brief Checks if the animation has been loaded successfully.
     * @return True if the animation has been loaded successfully, false otherwise.
     */
    bool isLoadedSuccessfully() const;

private:
    std::vector<unsigned int> keyframes; ///< The vector of keyframe indices.

    int currentKeyframe; ///< The index of the current keyframe.
    double frameTime; ///< The time between frames.

    bool isLoaded; ///< Indicates whether the animation has been loaded.

    unsigned int animTimerID; ///< The ID of the animation timer.

    bool looping; ///< Indicates whether the animation is looping.

    bool finished; ///< Indicates whether the animation has finished.
};
