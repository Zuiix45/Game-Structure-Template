#pragma once

#include "../util/Object.h"
#include "../util/Window.h"

#include <vector>
#include <memory>

#define RECTANGULAR_BUFFERS 0

#define cast std::shared_ptr // usage: cast<Object> obj = std::make_shared<Object>(60, 60, 60, 60, 60);
#define make std::make_shared // usage: cast<Object> obj = make<Object>(60, 60, 60, 60, 60);

#define getName(objectID) engine::getObjectName(objectID)
#define getID(objectName) engine::getObjectID(objectName)

/**
 * @brief The engine namespace contains functions for managing objects in the system.
 */
namespace engine {
    /**
     * @brief This namespace contains functions and utilities for managing the game engine.
     */
    
    /**
     * @brief This function initializes the engine and performs any necessary setup.
     * 
     * @param placeholderImagePath The path of the placeholder image.
     */
    void init(const char* placeholderImagePath);

    /**
     * @brief Creates an object in the specified layer.
     * 
     * @param layer The layer in which the object will be created.
     * @param objName The name of the object.
     * @param object The object to be created.
     * @return The unique identifier of the created object.
     */
    unsigned int registerObject(unsigned int layer, const std::string& objName, cast<Object> object);

    unsigned int getTotalObjectCount();

    /**
     * @brief Retrieves an object with the specified ID.
     *
     * @param objID The ID of the object to retrieve.
     * @return The object with the specified ID, or nullptr if no object is found.
     */
    cast<Object> getObject(unsigned int objID);

    /**
     * @brief Retrieves the ID of an object with the specified name.
     *
     * @param objName The name of the object.
     * @return The ID of the object, or 0 if no object is found.
     */
    unsigned int getObjectID(const std::string& objName);

    /**
     * @brief Retrieves the name of an object with the specified ID.
     *
     * @param objID The ID of the object.
     * @return The name of the object, or an empty string if no object is found.
     */
    std::string getObjectName(unsigned int objID);

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
     * @brief Retrieves the sprite path for the specified sprite name.
     * 
     * @param spriteName The name of the sprite.
     * @return The path of the sprite.
     */
    std::string getSpritePath(const std::string& spriteName);

    /**
     * @brief Converts a sprite name into a vector of strings.
     * 
     * @param spriteName The name of the sprite.
     * @return A vector of strings representing the sprite name.
     */
    std::vector<std::string> convertSpriteNameToList(const std::string& spriteName);
}
