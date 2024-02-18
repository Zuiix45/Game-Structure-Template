#pragma once

#include "../util/Object.h"
#include "../util/Animation.h"
#include "../util/Window.h"

/**
 * @brief The engine namespace contains functions for managing objects in the system.
 */
namespace engine {
    /**
     * @brief This function initializes the engine and performs any necessary setup.
     * 
     * @param placeholderImagePath The path of the placeholder image.
     */
    void init(const char* placeholderImagePath);

    unsigned int createContainer(unsigned int layer, const char* name);
    void deleteContainer(unsigned int id);
    void setLayer(unsigned int id, unsigned int layer);
    void drawAll(int windowWidth, int windowHeight);
    void closeAnimations(unsigned int id);
    void changeShaders(unsigned int id, const char* vertexShaderSource, const char* fragmentShaderSource);
    const char* getSpritePath(const char* name);
    void bindScriptToContainer(unsigned int id, const char* scriptName);
    std::vector<const char*> convertSprite(const char* spriteName);
}
