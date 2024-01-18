#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>

/**
 * @brief Represents a keyboard key event.
 */
class Key {
public:
    /**
     * Constructor for a Key event.
     * @param state The state of the key (pressed or released).
     * @param repeat Whether the key event is a repeat event.
     * @param scancode The SDL scancode of the key.
     */
    Key(Uint8 state, Uint8 repeat, SDL_Scancode scancode);

    /**
     * Updates the key event with new information.
     * @param state The state of the key (pressed or released).
     * @param repeat Whether the key event is a repeat event.
     */
    void update(Uint8 state, Uint8 repeat);

    /**
     * Checks if the key is currently down.
     * @return true if the key is down, false otherwise.
     */
    bool isDown();

    /**
     * Checks if the key event is a repeating event.
     * @return true if the key event is a repeat event, false otherwise.
     */
    bool isRepeating();

    /**
     * Gets the SDL key modifier flags associated with the key event.
     * @return The SDL key modifier flags.
     */
    SDL_Keymod getKeyMod();

private:
    Uint8 _state;
    Uint8 _repeat;
    SDL_Keymod _mod;
    SDL_Scancode _scancode;
};

/**
 * @brief Represents a mouse motion event.
 */
class MouseMotion {
public:
    MouseMotion();

    /**
     * Updates the coordinates of the mouse motion event.
     * @param mouseX The x-coordinate of the mouse.
     * @param mouseY The y-coordinate of the mouse.
     * @param globalX The x-coordinate of the mouse on the desktop.
     * @param globalY The y-coordinate of the mouse on the desktop.
     * 
     */
    void updateCoords(Sint32 mouseX, Sint32 mouseY, int globalX, int globalY);

    /**
     * Checks if the mouse is inside a specified rectangle.
     * @param topLeft The top-left corner of the rectangle.
     * @param bottomRight The bottom-right corner of the rectangle.
     * @return true if the mouse is inside the rectangle, false otherwise.
     */
    bool isInRectangle(glm::vec2 topLeft, glm::vec2 bottomRight);

    /**
     * Gets the location of the mouse.
     * @return The location as a glm::vec2.
     */
    glm::vec2 getLocation();

    /**
     * Gets the location of the mouse on the desktop.
     * @return The location as a glm::vec2.
     */
    glm::vec2 getGlobalLocation();

    /**
     * Returns the difference between old and new coordinates.
     */
    glm::vec2 getDiff();

    std::string toString();

protected:
    Sint32 _mouseX;
    Sint32 _mouseY;
    int _globalX;
    int _globalY;
    int _oldGlobalX;
    int _oldGlobalY;
};

/**
 * @brief Represents a mouse button event.
 */
class MouseButton : public MouseMotion {
public:
    /**
     * Constructor for a MouseButton event.
     * @param state The state of the mouse button (pressed or released).
     * @param clicks The number of clicks.
     * @param mouseX The x-coordinate of the mouse.
     * @param mouseY The y-coordinate of the mouse.
     */
    MouseButton(Uint8 state, Uint8 clicks, Sint32 mouseX, Sint32 mouseY);

    /**
     * Updates the mouse button event with new information.
     * @param state The state of the mouse button (pressed or released).
     * @param clicks The number of clicks.
     * @param mouseX The x-coordinate of the mouse.
     * @param mouseY The y-coordinate of the mouse.
     */
    void update(Uint8 state, Uint8 clicks, Sint32 mouseX, Sint32 mouseY);

    /**
     * Gets the number of clicks.
     * @return The number of clicks.
     */
    Uint8 getClickCount();

    /**
     * Checks if the mouse button is currently pressed.
     * @return true if the button is pressed, false otherwise.
     */
    bool isPressed();

    /**
     * Gets the SDL key modifier flags associated with the mouse button event.
     * @return The SDL key modifier flags.
     */
    SDL_Keymod getKeyMod();

private:
    Uint8 _state;
    Uint8 _clicks;
    SDL_Keymod _mod;
};

/**
 * @brief Represents a mouse wheel event.
 */
class MouseWheel : public MouseMotion {
public:
    MouseWheel();

    /**
     * Updates the mouse wheel event with new information.
     * @param mouseX The x-coordinate of the mouse.
     * @param mouseY The y-coordinate of the mouse.
     * @param scrollX The horizontal scrolling amount.
     * @param scrollY The vertical scrolling amount.
     * @param direction The scrolling direction.
     */
    void update(Sint32 mouseX, Sint32 mouseY, float scrollX, float scrollY, Uint32 direction);

private:
    float _scrollX;
    float _scrollY;
    Uint32 _direction;
};

/**
 * @brief Represents a text input event.
 */
class TextInput {
public:
    /**
     * Constructor for a TextInput event.
     * @param initialText The initial text.
     */
    TextInput(std::string initialText);

    /**
     * Default constructor for a TextInput event.
     */
    TextInput();

    /**
     * Adds a character to the text at the specified index.
     * @param _char The character to add.
     * @param index The index at which to add the character.
     */
    void addChar(char _char, int index);

    /**
     * Adds a character to the end of the text.
     * @param _char The character to add.
     */
    void addCharToEnd(char _char);

    /**
     * Removes a character from the text at the specified index.
     * @param index The index from which to remove the character.
     */
    void removeChar(int index);

    /**
     * Removes the last character from the text.
     */
    void removeLastChar();

    /**
     * Selects a range of characters in the text.
     * @param start The starting index of the selection.
     * @param end The ending index of the selection.
     */
    void choose(int start, int end);

    /**
     * Selects the entire text.
     */
    void chooseAll();

    /**
     * Deletes the currently selected text.
     */
    void deleteChoosed();

    /**
     * Pastes text from the clipboard at the specified index.
     * @param index The index at which to paste the text.
     */
    void pasteFromClipboard(int index);

    /**
     * Copies the currently selected text to the clipboard.
     */
    void copyToClipboard();

    /**
     * Gets the current text.
     * @return The current text.
     */
    std::string getText();

    /** Indicates if text is erased on press. */
    bool isErasedOnPress = false;

private:
    std::string text;
    unsigned int choosedStart;
    unsigned int choosedEnd;
};

namespace events {
    /**
     * Fetches events from the SDL event queue.
     */
    void fetchEvents();

    /**
     * @brief Check if SDL sent a quit event.
     */
    bool isQuitOccured();
}

namespace input {
    /**
     * Gets information about a specific key.
     * @param keycode The SDL keycode of the key.
     * @return A Key object with information about the key.
     */
    Key getKeyInfo(SDL_Keycode keycode);

    /**
     * Gets information about a specific mouse button.
     * @param button The SDL button index of the mouse button.
     * @return A MouseButton object with information about the mouse button.
     */
    MouseButton getMouseButtonInfo(Uint8 button);

    /**
     * Gets information about mouse motion.
     * @return A MouseMotion object with information about the mouse.
     */
    MouseMotion getMouseMotionInfo();

    /**
     * Gets information about mouse wheel events.
     * @return A MouseWheel object with information about the mouse wheel event.
     */
    MouseWheel getMouseWheelInfo();

    /**
     * Gets the path of the last file dropped onto the window.
     * @return The path of the last dropped file.
     */
    std::string getLastDroppedFile();

    /**
     * @brief Returns dragging amount of mouse.
     */
    glm::vec2 getDraggingAmount();

    /**
     * @brief Returns true if mouse is dragging.
     */
    bool isDragging();

    /**
     * Sets the TextInput object for handling text input events.
     * @param textInput The TextInput object.
     */
    void setTextInput(TextInput &textInput);

    /**
     * Clears the current TextInput object.
     */
    void clearTextInput();
}
