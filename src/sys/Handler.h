#pragma once

#include "../util/Object.h"

/**
 * @brief The handler namespace contains functions for managing objects in the system.
 */
namespace handler {
    /**
     * @brief This function initializes the handler and performs any necessary setup.
     */
    void init();

    /**
     * @brief Creates an object in the specified layer.
     * 
     * @param layer The layer in which the object will be created.
     * @param object A pointer to the object to be added to the object map.
     * @return The unique identifier of the created object.
     */
    unsigned int createObject(unsigned int layer, Object* object);

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
}
