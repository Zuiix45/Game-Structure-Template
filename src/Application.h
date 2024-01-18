#pragma once

#include "sys/Events.h"
#include "util/Window.h"

#include <map>

#define WINDOW_FLAGS SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS

#define WINDOW_WIDTH Application::getFocusedWindow()->getWidth()
#define WINDOW_HEIGHT Application::getFocusedWindow()->getHeight()

namespace cursors {
    extern SDL_Cursor* defaultCursor;
    extern SDL_Cursor* sizeWE; // horizontal resize
    extern SDL_Cursor* sizeNESW; // diagonal(North-East South-West) resize
    extern SDL_Cursor* sizeNS; // vertical resize
    extern SDL_Cursor* sizeNWSE; // diagonal(North-West South-East) resize
    extern SDL_Cursor* sizeAll;
    extern SDL_Cursor* handCursor;
}

/**
 * @brief The Application class provides methods for initializing and retrieving
 *        information about the application.
 */
class Application {
public:
    /**
     * @brief Initializes the application with the provided parameters.
     *
     * @param name The name of the application.
     * @param version The version of the application.
     * @param debugMode Whether the application is in debug mode.
     * @param width Width of the main window.
     * @param height Height of the main window.
     *
     * @return True if initialization is successful, false otherwise.
     */
    static bool initApp(const char* name, const char* version, bool debugMode, int width, int height);

    /**
     * @brief Deletes all pointers belongs this application.
     */
    static void destroyApp();

    /**
     * @brief Gets the name of the application.
     */
    static const char* getName();

    /**
     * @brief Gets the version of the application.
     */
    static const char* getVersion();

    /**
     * @brief Checks if the application is running in debug mode.
     */
    static bool isDebugging();

    /**
     * @brief Gets the time since the application started.
     * 
     * @return the duration of session
     */
    static double getSessionTime();

    /**
     * @brief Gets how many times buffers swapped in the last second.
     * 
     * @return frames(swapped buffers) per second
     */
    static int getFPS();

    /**
     * @brief Operates newly created frame
     * 
     * @param fpsCap set how many times swap buffers for a second. Leave empty or set 0 to not limit fps
     */
    static void operateFrame(int fpsCap = 0);

    /**
     * @brief Change the focused window
     * 
     * @param newWindow new focused window
     */
    static void changeFocus(Window* newWindow);

    /**
     * @brief Get the current focused Window 
     * 
     * @return Current focused window
     */
    static Window* getFocusedWindow();

private:
    static int sessionTimer;
    static int frameTimer; // this will reset every time when buffers swapped

    static double checkPoint; // indicates one second before sessionTimer, used on fps counting

    static int currentFPS;
    static int lastFPS; // counted fps for last second

    static const char* _name;
    static const char* _version;

    static bool _debugMode; // Internal variable indicating whether debug mode is enabled

    static bool isInitSuccess;

    static Window* focusedWindow;

    static GLenum currentError;
};
