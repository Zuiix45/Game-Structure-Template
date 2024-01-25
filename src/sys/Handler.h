#pragma once

#include "../util/Object.h"
#include "../util/Sprite.h"

/**
 * @brief The handler namespace contains functions for managing objects in the system.
 */
namespace handler {
    /**
     * @brief This function initializes the handler and performs any necessary setup.
     * 
     * @param placeholderImagePath The path of the placeholder image.
     */
    void init(const char* placeholderImagePath);

    /**
     * @brief Creates an object in the specified layer.
     * 
     * @param layer The layer in which the object will be created.
     * @param name The name of the object.
     * @param object A pointer to the object to be added to the object map.
     * @return The unique identifier of the created object.
     */
    unsigned int createObject(unsigned int layer, const char* name, Object* object);

    /**
     * @brief Deletes an object with the specified ID.
     * 
     * @param id The ID of the object to delete.
     * @return A pointer to the deleted object, or nullptr if no object is found.
     */
    Object* deleteObject(unsigned int id);

    /**
     * @brief Retrieves an object with the specified ID.
     * 
     * @param id The ID of the object to retrieve.
     * @return A pointer to the object with the specified ID, or nullptr if no object is found.
     */
    Object* getObject(unsigned int id);

    /**
     * @brief Retrieves an Object by its name.
     * 
     * @param name The name of the Object to retrieve.
     * @return A pointer to the Object if found, nullptr otherwise.
     */
    Object* getObject(const char* name);

    /**
     * @brief Retrieves the object ID associated with the given name.
     *
     * This function returns the unique identifier of an object based on its name.
     *
     * @param name The name of the object.
     * @return The object ID if found, otherwise 0.
     */
    unsigned int getObjectID(const char* name);

    /**
     * @brief Sets the layer of a specific object.
     *
     * @param id The ID of the object.
     * @param layer The layer to set.
     */
    void setLayer(unsigned int id, unsigned int layer);

    /**
     * @brief Draws all objects on the screen. 
     * This function should be called every frame.
     * All parameters will be normalized relative to window boundaries.
     * 
     * @param windowWidth The width of the window.
     * @param windowHeight The height of the window.
     */
    void drawAllObjects(int windowWidth, int windowHeight);

    /**
     * @brief Changes the shaders for a given ID. 
     * NOTE: Keep variable names the same as the default shaders.
     * 
     * @param id The ID of the object to change the shaders for.
     * @param vertexShaderSource The source code of the vertex shader. Default is an empty string.
     * @param fragmentShaderSource The source code of the fragment shader. Default is an empty string.
     */
    void changeShaders(unsigned int id, const char* vertexShaderSource = "", const char* fragmentShaderSource = "");

    /**
     * @brief Saves a sprite to a file.
     * 
     * @param name The name of the sprite.
     * @param path The path where the sprite will be saved.
     * @param flip Whether to flip the sprite vertically. Default is true.
     */
    void saveSprite(const char* name, const char* path, bool flip = true);

    /**
     * @brief Retrieves a sprite with the specified name.
     * 
     * @param name The name of the sprite to retrieve.
     * @return A pointer to the sprite with the specified name, or nullptr if no sprite is found.
     */
    Sprite* getSprite(const char* name);
}
