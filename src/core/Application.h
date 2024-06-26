#pragma once

#include "../util/Window.h"
#include "../sys/Logger.h"

#include <map>
#include <memory>

#define WINDOW_WIDTH App::getFocusedWindow()->getWidth()
#define WINDOW_HEIGHT App::getFocusedWindow()->getHeight()

/**
 * @brief The Application class provides methods for initializing and retrieving
 *        information about the application.
 */
class App {
public:
    /**
     * @brief Initializes the application with the provided parameters.
     * 
     * @param name The name of the application.
     * @param version The version of the application.
     * @param width The width of the application window.
     * @param height The height of the application window.
     * @param resourcesFolderPath The path to the resources folder.
     * @param defaultFontName The name of the default font.
     * @param defaultFontSize The size of the default font.
     * @param args The arguments passed to the application.
     *
     * @return True if initialization is successful, false otherwise.
     */
    static bool initApp(const char* name, const char* version, 
            int width, int height, const char* resourcesFolderPath, 
            const char* defaultFontName, int defaultFontSize, char* args[]);

    /**
     * @brief Deletes all pointers belongs this application.
     */
    static void destroyApp();

    /**
     * @brief Gets the name of the application.
     */
    static const char* getAppName();

    /**
     * @brief Gets the version of the application.
     */
    static const char* getVersion();

    /**
     * @brief Checks if the application is running in debug mode.
     */
    static bool isDebugging();

    /**
     * @brief Checks if the application is currently running.
     * 
     * @return true if the application is running, false otherwise.
     */
    static bool isRunning();

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
     * @brief Starts game loop
     * 
     * @param fpsCap set how many times swap buffers for a second. Leave empty or set 0 to not limit fps
     */
    static void startLoop(int fpsCap = 0);

    /**
     * @brief Change the focused window
     * 
     * @param newWindow new focused window
     */
    static void changeFocus(std::shared_ptr<Window> newWindow);

    /**
     * @brief Get the current focused Window 
     * 
     * @return Current focused window
     */
    static std::shared_ptr<Window> getFocusedWindow();

    /**
     * Renders the statistics of the game.
     */
    static void drawStats();

    static bool isShowingStats();

    static void toggleStats();

private:
    static int sessionTimer;
    static int frameTimer; /**< this will reset every time when buffers swapped except vsync is on and fps cap is off. */

    static double checkPoint; /**< indicates one second before sessionTimer, used on fps counting. */

    static int currentFPS;
    static int lastFPS; /**< counted fps for last second. */

    static const char* _name;
    static const char* _version;

    static bool _debugMode; /**< Internal variable indicating whether debug mode is enabled. */

    static bool showStats;

    static bool isInitSuccess;

    static std::shared_ptr<Window> focusedWindow;

    static GLenum currentError;
};
