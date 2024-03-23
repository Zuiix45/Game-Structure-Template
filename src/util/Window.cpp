#include "Window.h"

#include "../sys/Logger.h"
#include "../sys/Files.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <map>

#include <glm/gtc/matrix_transform.hpp>

/* Implementation of Window class */

Window::Window(const char* title, int width, int height) {
    
    // Create an SDL window with the specified dimensions and title
    _GLFWWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwSetWindowPos(_GLFWWindow, 300, 300);

    _x = 300;
    _y = 300;

    _width = width;
    _height = height;

    _projectionMatrix = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

    if (!_GLFWWindow) return;

    glfwMakeContextCurrent(_GLFWWindow);

    // load Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        logError("OpenGL could not initialized correctly. ", OPENGL_INITIALIZATION_ERROR);

    // Vsync
    setVsync(0);
}

Window::~Window() { glfwDestroyWindow(_GLFWWindow); }
void Window::hide() { glfwHideWindow(_GLFWWindow); }
void Window::show() { glfwShowWindow(_GLFWWindow); }

void Window::renderFrame() {
    glfwSwapBuffers(_GLFWWindow);
}

void Window::clearFrame() {
    int width = getWidth();
    int height = getHeight();

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setVsync(bool interval) {
    glfwSwapInterval(interval);
    _interval = interval;
}

void Window::setFullscreen(bool fullscreen, int width, int height) {
    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(_GLFWWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        glfwSetWindowMonitor(_GLFWWindow, NULL, _x, _y, width, height, 0);
    }

    updateWindowBounds();
}

void Window::setBounds(int newWidth, int newHeight) {
    glfwSetWindowSize(_GLFWWindow, newWidth, newHeight);

    _width = newWidth;
    _height = newHeight;

    _projectionMatrix = glm::ortho(0.0f, static_cast<float>(newWidth), static_cast<float>(newHeight), 0.0f, -1.0f, 1.0f);
}

void Window::setLocation(int x, int y) {
    glfwSetWindowPos(_GLFWWindow, x, y);

    _x = x;
    _y = y;
}

bool Window::isVsyncOn() { return _interval; }
int Window::getX() { return _x; }
int Window::getY() { return _y; }
int Window::getWidth() { return _width; }
int Window::getHeight() { return _height; }

void Window::updateWindowBounds() {
    int width, height;
    glfwGetWindowSize(_GLFWWindow, &width, &height);

    _width = width;
    _height = height;

    _projectionMatrix = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

    int x, y;
    glfwGetWindowPos(_GLFWWindow, &x, &y);

    _x = x;
    _y = y;
}

glm::mat4 Window::getProjectionMatrix() {
    return _projectionMatrix;
}

GLFWwindow* Window::getGLFWWindow() { return _GLFWWindow; }
