#pragma once

#include "../util/Window.h"

struct KeyEvent {
    int key;
    int scancode;
    int action;
    int mods;
};

struct MouseButtonEvent {
    int button;
    int action;
    int mods;
    double x;
    double y;
};

namespace callbacks {
    void init(GLFWwindow* window);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void charCallback(GLFWwindow* window, unsigned int codepoint);
    void dropCallback(GLFWwindow* window, int count, const char** paths);
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    void monitorCallback(GLFWmonitor* monitor, int event);
    void charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
    void joystickCallback(int jid, int event);
    void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    void windowPosCallback(GLFWwindow* window, int xpos, int ypos);
    void windowSizeCallback(GLFWwindow* window, int width, int height);
    void cursorEnterCallback(GLFWwindow* window, int entered);
    void windowCloseCallback(GLFWwindow* window);
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void windowFocusCallback(GLFWwindow* window, int focused);
    void windowIconifyCallback(GLFWwindow* window, int iconified);
    void windowRefreshCallback(GLFWwindow* window);
    void windowMaximizeCallback(GLFWwindow* window, int maximized);
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void windowContentScaleCallback(GLFWwindow* window, float xScale, float yScale);
}

namespace input {
    KeyEvent getKeyState(int key);
    MouseButtonEvent getMouseButtonState(int button);
    
    void enableTextInput();
    void disableTextInput();
    void clearTextInput();
    std::string getTextInput();

    double getMouseX();
    double getMouseY();

    bool isFocused();

    void pollEvents();
}