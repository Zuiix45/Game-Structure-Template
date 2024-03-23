#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

/**
 * @brief Class representing a window for graphics rendering.
 */

class Window {
public:
    /**
     * @brief Default constructor
     */
    Window(const char* title, int width, int height);

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
     * @param interval 1: enable, 0: disable
     */
    void setVsync(bool interval);

    /**
     * @brief Sets the fullscreen mode of the window.
     * 
     * @param fullscreen True to enable fullscreen mode, false otherwise.
     * @param width The width of the window.
     * @param height The height of the window.
     */
    void setFullscreen(bool fullscreen, int width = 0, int height = 0);

    /**
     * @brief Check if vsync is enabled.
     */
    bool isVsyncOn();

    /**
     * @brief Gets the X coordinate of the window.
     * 
     * @return The X coordinate of the window.
     */
    int getX();

    /**
     * @brief Gets the y-coordinate of the window.
     * 
     * @return The y-coordinate of the window.
     */
    int getY();

    /**
     * @brief Get the window width.
     */
    int getWidth();

    /**
     * @brief Get the window height.
     */
    int getHeight();

    /**
     * @brief Gets new windows bounds from GLFW and updates local variables.
     * 
     */
    void updateWindowBounds();

    glm::mat4 getProjectionMatrix();

    /**
     * @brief Retrieves the GLFW window object.
     * 
     * @return A pointer to the GLFWwindow object.
     */
    GLFWwindow* getGLFWWindow();

private:
    GLFWwindow* _GLFWWindow; /**< Pointer to the GLFW window. */

    glm::mat4 _projectionMatrix;

    int _width;
    int _height;
    int _x;
    int _y;

    bool _interval;
    bool _fullscreen;
};
 