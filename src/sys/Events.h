#pragma once

#include "../util/Window.h"

#include "inputdefs.h"

struct KeyEvent {
    Key key;
    Scancode scancode;
    State action;
    Mod mods;
};

struct MouseButtonEvent {
    MouseButton button;
    State action;
    Mod mods;
    double x;
    double y;
};

namespace input {
    /**
     * Initializes the input system with the specified GLFW window.
     * @param window The GLFW window to associate with the input system.
     */
    void init(GLFWwindow* window);
    
    /**
     * Checks if the specified key is currently pressed.
     * @param key The key to check.
     * @return True if the key is currently pressed, false otherwise.
     */
    bool isKeyPressed(Key key);
    
    /**
     * Checks if the specified key was released since the last frame.
     * @param key The key to check.
     * @return True if the key was released, false otherwise.
     */
    bool isKeyReleased(Key key);
    
    /**
     * Checks if the specified key is currently being held down.
     * @param key The key to check.
     * @return True if the key is being held down, false otherwise.
     */
    bool isKeyHeld(Key key);
    
    /**
     * Checks if the specified key is currently pressed or being held down.
     * @param key The key to check.
     * @return True if the key is pressed or held down, false otherwise.
     */
    bool isPressedOrHeld(Key key);

    /**
     * Gets the total scroll amount in the X direction since the last frame.
     * @return The total scroll amount in the X direction.
     */
    double getTotalScrollX();
    
    /**
     * Gets the total scroll amount in the Y direction since the last frame.
     * @return The total scroll amount in the Y direction.
     */
    double getTotalScrollY(); 

    /**
     * Gets the state of the specified key.
     * @param key The key to check.
     * @return The state of the key.
     */
    KeyEvent getKeyState(Key key);
    
    /**
     * Gets the state of the specified mouse button.
     * @param button The mouse button to check.
     * @return The state of the mouse button.
     */
    MouseButtonEvent getMouseButtonState(MouseButton button);

    /**
     * Gets the scancode of the specified key.
     * @param key The key to get the scancode for.
     * @return The scancode of the key.
     */
    Scancode getScancode(Key key);
    
    /**
     * Enables text input for the window.
     */
    void enableTextInput();
    
    /**
     * Disables text input for the window.
     */
    void disableTextInput();
    
    /**
     * Clears the text input buffer.
     */
    void clearTextInput();
    
    /**
     * Gets the current text input.
     * @return The current text input.
     */
    std::string getTextInput();

    /**
     * Gets the X position of the mouse cursor.
     * @return The X position of the mouse cursor.
     */
    double getMouseX();
    
    /**
     * Gets the Y position of the mouse cursor.
     * @return The Y position of the mouse cursor.
     */
    double getMouseY();

    /**
     * Checks if the window is currently focused.
     * @return True if the window is focused, false otherwise.
     */
    bool isFocused();

    /**
     * Polls for input events and updates the input state.
     */
    void pollEvents();
}
