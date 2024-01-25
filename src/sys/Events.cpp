#include "Events.h"

#include "Logger.h"

#include "../util/Window.h"

#include <map>

namespace {
    bool quitOccurred = false;

    bool dragging;
    glm::vec2 draggingStartCoords;
    glm::vec2 draggingDelta;

    // Maps to store key and mouse button states
    std::map<int, Key*> keyMap;
    std::map<int, MouseButton*> mouseMap;

    MouseMotion* mouseMotion = new MouseMotion(); // Instance of MouseMotion
    MouseWheel* mouseWheel = new MouseWheel();   // Instance of MouseWheel

    std::string lastDroppedFile;  // Stores the path of the last dropped file

    TextInput* currentTextInput;  // Pointer to the current text input

    // Helper function to handle key events
    void handleKeyEvent(SDL_KeyboardEvent e) {
        // text erasing
        if (currentTextInput != nullptr && e.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
            if (e.repeat)
                currentTextInput->removeLastChar();

            // erase one char per press
            else if (e.type == SDL_KEYDOWN && !currentTextInput->isErasedOnPress) {
                currentTextInput->removeLastChar();
                currentTextInput->isErasedOnPress = true;
            }

            else if (e.type == SDL_KEYUP)
                currentTextInput->isErasedOnPress = false;
        }

        if (keyMap[(int)e.keysym.sym] != nullptr) {
            keyMap[(int)e.keysym.sym]->update(e.state, e.repeat);
            return;
        }

        keyMap[(int)e.keysym.sym] = new Key(e.state, e.repeat, e.keysym.scancode);
    }

    // Helper function to handle mouse button events
    void handleMouseButtonEvent(SDL_MouseButtonEvent e) {
        if (mouseMap[(int)e.button] == nullptr)
            mouseMap[(int)e.button] = new MouseButton(e.state, e.clicks, e.x, e.y);

        else if (mouseMap[(int)e.button] != nullptr)
            mouseMap[(int)e.button]->update(e.state, e.clicks, e.x, e.y);

        // Handle dragging
        if (e.button == SDL_BUTTON_LEFT) {
            dragging = e.state;

            if (dragging) {
                int dx, dy;
                SDL_GetGlobalMouseState(&dx, &dy);
                draggingStartCoords = {dx, dy};
            }
        }
    }

    // Helper function to handle mouse motion events
    void handleMouseMotionEvent(SDL_MouseMotionEvent e) {
        Sint32 _mouseX, _mouseY;
        int _globalX, _globalY;
        SDL_GetGlobalMouseState(&_globalX, &_globalY);
        SDL_GetMouseState(&_mouseX, &_mouseY);
        mouseMotion->updateCoords(_mouseX, _mouseY, _globalX, _globalY);

        if (dragging) {
            draggingDelta = mouseMotion->getGlobalLocation() - draggingStartCoords;
            draggingStartCoords = mouseMotion->getGlobalLocation();
        }
    }

    // Helper function to handle mouse wheel events
    void handleMouseWheelEvent(SDL_MouseWheelEvent e) {
        mouseWheel->update(e.mouseX, e.mouseY, e.preciseX, e.preciseY, e.direction);
    }

    // Helper function to handle file drop events
    void handleDropEvent(SDL_DropEvent e) {
        char* filePath = e.file;
        lastDroppedFile = filePath;
        SDL_free(filePath);
    }

    // Helper function to handle text input events
    void handleTextInput(SDL_TextInputEvent e) {
        if (currentTextInput != nullptr)
            currentTextInput->addCharToEnd(*e.text);
    }
}

/* Implementation of events namespace */

void events::fetchEvents() {
    SDL_Event e;

    draggingDelta = {0, 0};

    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                quitOccurred = true;
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                handleKeyEvent(e.key);
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                handleMouseButtonEvent(e.button);
                break;

            case SDL_MOUSEMOTION:
                handleMouseMotionEvent(e.motion);
                break;

            case SDL_MOUSEWHEEL:
                handleMouseWheelEvent(e.wheel);
                break;

            case SDL_DROPFILE:
                handleDropEvent(e.drop);
                break;

            case SDL_TEXTINPUT:
                handleTextInput(e.text);
                break;
        }
    }
}

bool events::isQuitOccurred() {
    return quitOccurred;
}

/* Implementation of input namespace */

Key input::getKeyInfo(SDL_Keycode keycode) {
    Key *key = keyMap[(int)keycode];
    
    if (key != nullptr)
        return *key;

    return Key(0, 0, SDL_SCANCODE_UNKNOWN); // empty key for unhandled key code
}

Key input::getKeyInfo(SDL_Scancode scancode) {
    Key *key = keyMap[(int)scancode];

    if (key != nullptr)
        return *key;

    return Key(0, 0, SDL_SCANCODE_UNKNOWN); // empty key for unhandled scan code
}

bool input::isKeyDown(SDL_Keycode keycode) {
    Key *key = keyMap[(int)keycode];

    if (key != nullptr)
        return key->isDown();

    return false;
}

MouseButton input::getMouseButtonInfo(Uint8 button) {
    MouseButton *mb = mouseMap[(int)button];

    if (mb != nullptr)
        return *mb;

    return MouseButton(0, 0, 0, 0); // empty key for unhandled mouse button
}

MouseMotion input::getMouseMotionInfo() {
    return *mouseMotion;
}

MouseWheel input::getMouseWheelInfo() {
    return *mouseWheel;
}

std::string input::getLastDroppedFile() {
    return lastDroppedFile;
}

glm::vec2 input::getDraggingAmount() {
    if (dragging) {
        return draggingDelta;
    }

    return {0, 0};
}

bool input::isDragging() {
    return dragging;
}

void input::setTextInput(TextInput &textInput) {
    currentTextInput = &textInput;
}

void input::clearTextInput() {
    currentTextInput = nullptr;
}

/* Implementation of Key Class */

Key::Key(Uint8 state, Uint8 repeat, SDL_Scancode scancode) {
    _state = state;
    _repeat = repeat;
    _scancode = scancode;

    _mod = SDL_GetModState();
}

void Key::update(Uint8 state, Uint8 repeat) {
    _state = state;
    _repeat = repeat;

    _mod = SDL_GetModState();
}

bool Key::isDown() {
    if (_state == SDL_PRESSED)
        return true;

    return false;
}

bool Key::isRepeating() {
    return _repeat;
}

SDL_Keymod Key::getKeyMod() {
    return _mod;
}

/* Implementation of MouseMotion Class */

MouseMotion::MouseMotion() {
    SDL_GetGlobalMouseState(&_globalX, &_globalY);
    SDL_GetMouseState(&_mouseX, &_mouseY);

    _oldGlobalX = _mouseX;
    _oldGlobalY = _mouseY;
}

void MouseMotion::updateCoords(Sint32 mouseX, Sint32 mouseY, int globalX, int globalY) {
    _mouseX = mouseX;
    _mouseY = mouseY;
    _oldGlobalX = _globalX;
    _oldGlobalY = _globalY;
    _globalX = globalX;
    _globalY = globalY;
}

bool MouseMotion::isInRectangle(glm::vec2 topLeft, glm::vec2 bottomRight) {
    float minX = topLeft.x;
    float minY = topLeft.y;
    float maxX = bottomRight.x;
    float maxY = bottomRight.y;

    float x = _mouseX;
    float y = _mouseY;

    if (maxX > x && maxY > y && minX < x && minY < y)
        return true;

    return false;
}

glm::vec2 MouseMotion::getLocation() {
    return glm::vec2((double)_mouseX, (double)_mouseY);
}

glm::vec2 MouseMotion::getGlobalLocation() {
    return glm::vec2((double)_globalX, (double)_globalY);
}

glm::vec2 MouseMotion::getDiff() {
    return glm::vec2((double)(_globalX - _oldGlobalX), (double)(_globalY - _oldGlobalY));
}

std::string MouseMotion::toString() {
    return "x: " + std::to_string(_mouseX) + ", y: " + std::to_string(_mouseY);
}

/* Implementation of MouseButton Class */

MouseButton::MouseButton(Uint8 state, Uint8 clicks, Sint32 mouseX, Sint32 mouseY) {
    _state = state;
    _clicks = clicks;
    _mouseX = mouseX;
    _mouseY = mouseY;

    _mod = SDL_GetModState();
}

void MouseButton::update(Uint8 state, Uint8 clicks, Sint32 mouseX, Sint32 mouseY) {
    _state = state;
    _clicks = clicks;
    _mouseX = mouseX;
    _mouseY = mouseY;

    _mod = SDL_GetModState();
}

SDL_Keymod MouseButton::getKeyMod() {
    return _mod;
}

Uint8 MouseButton::getClickCount() {
    return _clicks;
}

bool MouseButton::isPressed() {
    if (_state == SDL_PRESSED)
        return true;

    return false;
}

/* Implementation of MouseWheel Class */

MouseWheel::MouseWheel() {
    _mouseX = 0;
    _mouseY = 0;
    _scrollX = 0;
    _scrollY = 0;
    _direction = 0;
}

void MouseWheel::update(Sint32 mouseX, Sint32 mouseY, float scrollX, float scrollY, Uint32 direction) {
    _mouseX = mouseX;
    _mouseY = mouseY;
    _scrollX = scrollX;
    _scrollY = scrollY;
    _direction = direction;
}

/* Implementation of TextInput Class */

TextInput::TextInput(std::string initialText) {
    text = initialText;

    selectedStart = 0;
    selectedEnd = 0;
}

TextInput::TextInput() {
    text = "";

    selectedStart = 0;
    selectedEnd = 0;
}

void TextInput::addChar(char _char, int index) {
    if ((int)_char < 0) return;
    if (index > text.size()) return;
    text = text.substr(0, index) + _char + text.substr(index, text.size()-index);
}

void TextInput::addCharToEnd(char _char) {
    if ((int)_char < 0) return;
    text += _char;
}

void TextInput::removeChar(int index) {
    if (index > text.size()) return;
    text = text.substr(0, index) + text.substr(index+1, text.size()-index-1);
}

void TextInput::removeLastChar() {
    text = text.substr(0, text.size()-1);
}

void TextInput::select(int start, int end) {
    selectedStart = start;
    selectedEnd = end;
}

void TextInput::chooseAll() {
    selectedStart = 0;
    selectedEnd = text.size();
}

void TextInput::deleteSelected() {
    if (selectedEnd-selectedStart == 0) return;

    text = text.substr(0, selectedStart) + text.substr(selectedEnd, text.size()-selectedEnd-1);

    selectedStart = 0;
    selectedEnd = 0;
}

void TextInput::pasteFromClipboard(int index) {
    if (selectedEnd-selectedStart != 0) {
        index = selectedStart;
        deleteSelected();
    }

    char* copyTxt = SDL_GetClipboardText();
    text = text.substr(0, index) + copyTxt + text.substr(index, text.size()-index);
    SDL_free(copyTxt);
}

void TextInput::copyToClipboard() {
    if (selectedEnd-selectedStart == 0) return;

    if (SDL_SetClipboardText(text.substr(selectedStart, selectedEnd-selectedStart).c_str()) < 0) logSDLError();
}

std::string TextInput::getText() {
    return text;
}
