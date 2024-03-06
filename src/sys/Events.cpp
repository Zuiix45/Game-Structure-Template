#include "Events.h"

#include "Logger.h"

#include <vector>
#include <map>

namespace {
    // text input
    bool textInputEnabled = false;
    std::string textInput = "";

    // keyboard input
    KeyEvent lastKeyEvent;
    std::map<int, KeyEvent> keyStates;

    // mouse input
    MouseButtonEvent lastMouseButtonEvent;
    std::map<int, MouseButtonEvent> mouseButtonStates;

    // mouse position
    double mouseX;
    double mouseY;

    // scroll input
    double scrollX;
    double scrollY;

    // window focus
    bool windowFocused = false;

    // window iconify
    bool windowIconified = false;

    // dropped files
    std::vector<std::string> lastDroppedFiles;

    // joysticks
    std::vector<int> joysticks; // holds active jids

    // cursor enter
    bool cursorEntered = false;
}

void callbacks::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window, charCallback);
    glfwSetDropCallback(window, dropCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetMonitorCallback(monitorCallback);
    glfwSetCharModsCallback(window, charModsCallback);
    glfwSetJoystickCallback(joystickCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetWindowPosCallback(window, windowPosCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    glfwSetWindowCloseCallback(window, windowCloseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);
    glfwSetWindowIconifyCallback(window, windowIconifyCallback);
    glfwSetWindowRefreshCallback(window, windowRefreshCallback);
    glfwSetWindowMaximizeCallback(window, windowMaximizeCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetWindowContentScaleCallback(window, windowContentScaleCallback);
}

void callbacks::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    lastKeyEvent = {key, scancode, action, mods};
    keyStates[key] = lastKeyEvent;
}

void callbacks::charCallback(GLFWwindow* window, unsigned int codepoint) {
    if (textInputEnabled)
        textInput += codepoint;
}

void callbacks::dropCallback(GLFWwindow* window, int count, const char** paths) {
    lastDroppedFiles.clear();
    for (int i = 0; i < count; i++) {
        lastDroppedFiles.push_back(paths[i]);
    }
}

void callbacks::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    scrollX = xoffset;
    scrollY = yoffset;
}

void callbacks::monitorCallback(GLFWmonitor* monitor, int event) {}
void callbacks::charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods) {}

void callbacks::joystickCallback(int jid, int event) {
    if (event == GLFW_CONNECTED) {
        joysticks.push_back(jid);
    } else if (event == GLFW_DISCONNECTED) {
        for (int i = 0; i < joysticks.size(); i++) {
            if (joysticks[i] == jid) {
                joysticks.erase(joysticks.begin() + i);
                break;
            }
        }
    }
}

void callbacks::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

void callbacks::windowPosCallback(GLFWwindow* window, int xpos, int ypos) {}
void callbacks::windowSizeCallback(GLFWwindow* window, int width, int height) {}

void callbacks::cursorEnterCallback(GLFWwindow* window, int entered) {
    cursorEntered = entered;
}

void callbacks::windowCloseCallback(GLFWwindow* window) {}

void callbacks::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    lastMouseButtonEvent = {button, action, mods, x, y};
    mouseButtonStates[button] = lastMouseButtonEvent;
}

void callbacks::windowFocusCallback(GLFWwindow* window, int focused) {
    windowFocused = focused;
}

void callbacks::windowIconifyCallback(GLFWwindow* window, int iconified) {
    windowIconified = iconified;
}

void callbacks::windowRefreshCallback(GLFWwindow* window) {}
void callbacks::windowMaximizeCallback(GLFWwindow* window, int maximized) {}

void callbacks::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void callbacks::windowContentScaleCallback(GLFWwindow* window, float xScale, float yScale) {}

/// -- input namespace functions

KeyEvent input::getKeyState(int key) { return keyStates[key]; }
MouseButtonEvent input::getMouseButtonState(int button) { return mouseButtonStates[button]; }
void input::enableTextInput() { textInputEnabled = true; }
void input::disableTextInput() { textInputEnabled = false; }
void input::clearTextInput() { textInput = ""; }
std::string input::getTextInput() { return textInput; }
double input::getMouseX() { return mouseX; }
double input::getMouseY() { return mouseY; }
bool input::isFocused() { return windowFocused; }
void input::pollEvents() { glfwPollEvents(); }
