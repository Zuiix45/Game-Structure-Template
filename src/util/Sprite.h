#pragma once

#include "../sys/Timer.h"

#include <vector>

class Sprite {
public:
    /**
     * @brief Represents a sprite object.
     *
     * This class is used to create and manipulate sprite objects.
     * Sprites can be loaded from an image file and flipped horizontally.
     *
     * @param imagePath The path to the image file used for the sprite.
     * @param flip      Whether the sprite should be flipped horizontally.
     */
    Sprite(const char* imagePath, bool flip = true);
    ~Sprite();

    /**
     * Activates the texture for rendering.
     */
    void activateTexture() const;

    /**
     * @brief Get the texture ID of the sprite.
     * 
     * @return The texture ID of the sprite.
     */
    unsigned int getTextureID() const;

    /**
     * @brief Checks if the sprite is loaded successfully.
     * 
     * @return true if the sprite is loaded successfully, false otherwise.
     */
    bool isLoadedSuccessfully() const;

private:
    unsigned int textureID;

    bool isLoaded;
};

class Animation {
public:
    Animation(Sprite* frame);
    Animation(std::vector<Sprite*> keyframes, int fps=60, float speed=1.0f);

    void step();

    bool isLoadedSuccessfully() const;

private:
    std::vector<Sprite*> keyframes;

    int fps;
    int currentKeyframe;
    double frameTime;

    bool isLoaded;

    unsigned int animTimerID;
};
