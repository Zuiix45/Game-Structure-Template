#pragma once

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#define ENABLE_ADAPTIVE_VSYNC -1
#define ENABLE_VSYNC 1
#define DISABLE_VSYNC 0

/**
 * @brief Class representing a window for graphics rendering.
 */

class Window {
private:
    SDL_Window* _SDLWindow; /**< Pointer to the SDL window. */
    SDL_GLContext _SDLGLContext; /**< Pointer to the SDL GL context. */

    int _width;
    int _height;

    glm::vec2 _location;

public:
    /**
     * @brief Default constructor
     */
    Window(const char* title, int width, int height, Uint32 flags);

    /**
     * @brief Destroy the Window object
     * 
     */
    ~Window();

    /**
     * @brief Hide the window.
     */
    void hide();

    /**
     * @brief Show the window.
     */
    void show();

    /**
     * @brief Create new empty frame
     */
    void newFrame();

    /**
     * @brief Render the current frame
     */
    void renderFrame();

    /**
     * @brief clear the last rendered frame
     */
    void clearFrame();

    /**
     * @brief Set window size.
     *
     * @param newWidth The new width of the window.
     * @param newHeight The new height of the window.
     */
    void setBounds(int newWidth, int newHeight);

    /**
     * @brief Set window position.
     *
     * @param x The x-coordinate of the window position.
     * @param y The y-coordinate of the window position.
     */
    void setLocation(int x, int y);

    /**
     * @brief Enable or disable vsync. Enables normal if adaptive fails.
     *
     * @param interval 1: enable, 0: disable, -1: adaptive
     */
    void setVsync(int interval);

    /**
     * @brief Check if vsync is enabled.
     */
    bool isVsyncOn();

    /**
     * @brief Get the window location.
     *
     * @return The location of the window as a 2D vector.
     */
    glm::vec2 getLocation();

    /**
     * @brief Get the window width.
     */
    int getWidth();

    /**
     * @brief Get the window height.
     */
    int getHeight();

    /**
     * @brief Get the SDL window pointer.
     */
    SDL_Window* getSDLWindow();

    /**
     * @brief Get the SDL renderer pointer.
     */
    SDL_Renderer* getRenderer();
};
 