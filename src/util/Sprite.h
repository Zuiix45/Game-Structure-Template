#pragma once

#include <vector>

class Sprite {
public:
    /**
     * @brief Represents a sprite object.
     * 
     * The Sprite class is used to create and manipulate sprite objects in a game or application.
     * It provides functionality for loading and rendering textures, as well as flipping the sprite horizontally.
     * 
     * @param firstTexturePath The path to the first texture of the sprite.
     * @param flip Whether to flip the sprite horizontally. Default is true.
     */
    Sprite(const char* firstTexturePath, bool flip = true);

    /**
     * @brief Adds a texture to the sprite.
     * 
     * @param path The path to the texture file.
     * @param flip Whether to flip the texture vertically or not. Default is true.
     */
    void addTexture(const char* path, bool flip = true);

    /**
     * @brief Deletes the texture at the specified index.
     *
     * @param index The index of the texture to delete.
     */
    void deleteTexture(unsigned int index);

    /**
     * @brief Gets the number of textures used by the sprite.
     * 
     * @return The number of textures used by the sprite.
     */
    int getTextureCount() const;

    /**
     * Activates the textures for the sprite.
     */
    void activateTextures() const;

private:
    std::vector<unsigned int> textures;
};
