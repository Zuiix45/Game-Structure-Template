#include "Application.h"

#include "sys/Logger.h"
#include "sys/Timer.h"

#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

SDL_Cursor* cursors::defaultCursor;
SDL_Cursor* cursors::sizeWE;
SDL_Cursor* cursors::sizeNESW;
SDL_Cursor* cursors::sizeNS;
SDL_Cursor* cursors::sizeNWSE;
SDL_Cursor* cursors::sizeAll;
SDL_Cursor* cursors::handCursor;

int Application::sessionTimer;
int Application::frameTimer;
double Application::checkPoint;
int Application::currentFPS;
int Application::lastFPS ;
const char* Application::_name;
const char* Application::_version;
bool Application::_debugMode;
bool Application::isInitSuccess;
Window* Application::focusedWindow;
GLenum Application::currentError;

/* Implementation of Application class */

bool Application::initApp(const char* name, const char* version, bool debugMode, int width, int height) {
    if (isInitSuccess) return true;

    _name = name;
    _version = version;
    _debugMode = debugMode;

    // Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0) {
        logSDLError();
        return false;
    }

    // SDL Attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_BlendMode(SDL_BLENDMODE_BLEND);

    // Create the main window for application
    #ifdef _WIN32
        SetProcessDPIAware();
    #endif
    
    focusedWindow = new Window(name, width, height, WINDOW_FLAGS);

    if (!focusedWindow) {
        logError("Main window cannot be created. ", 0);
        logSDLError();
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Create Cursors
    cursors::defaultCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    cursors::sizeWE = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    cursors::sizeNESW = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    cursors::sizeNS = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    cursors::sizeNWSE = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    cursors::sizeAll = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    cursors::handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

    // Create timers
    sessionTimer = timer::createTimer();
    frameTimer = timer::createTimer();

    currentFPS = 0;
    lastFPS = 0;
    checkPoint = 0;

    return isInitSuccess; // Initialization was successful
}

void Application::destroyApp() {
    delete focusedWindow;

    timer::killTimer(sessionTimer);
    timer::killTimer(frameTimer);

    isInitSuccess = false;

    SDL_Quit();
}

const char* Application::getName() {
    return _name;
}

const char* Application::getVersion() {
    return _version;
}

bool Application::isDebugging() {
    return _debugMode;
}

double Application::getSessionTime() {
    return timer::getTimeDiff(sessionTimer);
}

int Application::getFPS() {
    return lastFPS;
}

void Application::operateFrame(int fpsCap) {
    // Render newly created frame
    focusedWindow->renderFrame();

    // update lastFPS every second
    double diff = timer::getTimeDiff(sessionTimer);

    if (diff - checkPoint >= 1000) {
        checkPoint = diff;

        lastFPS = currentFPS;
        currentFPS = 0;
    }

    currentFPS++;

    // sleep for remaining time to cap frames
    if (fpsCap != 0 && !focusedWindow->isVsyncOn()) {
        double maxDelay = 1000.0 / fpsCap;

        timer::delay((maxDelay - timer::getTimeDiff(frameTimer)));
        timer::resetTimer(frameTimer);
    }

    // Clear Frame
    focusedWindow->clearFrame();

    GLenum newError = glGetError();
    if (newError != currentError) logError("OpenGL error occured", newError);
    currentError = newError;
}

void Application::changeFocus(Window* newWindow) {
    delete focusedWindow;
    focusedWindow = newWindow;
}

Window* Application::getFocusedWindow() {
    return focusedWindow;
}
