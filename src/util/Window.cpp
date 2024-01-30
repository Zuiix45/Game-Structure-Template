#include "Window.h"

#include "../sys/Logger.h"
#include "../sys/Events.h"
#include "../sys/Files.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <map>

/* Implementation of Window class */

Window::Window(const char* title, int width, int height, Uint32 flags) {
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0, &mode);

    // Create an SDL window with the specified dimensions and title
    _SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

    _location = {mode.w/2 - width/2, mode.h/2 - height/2};

    _width = width;
    _height = height;

    if (_SDLWindow == nullptr) {
        logError("Window could not be created.", 0);
        logSDLError();
        return;
    }

    // Create Renderer for 2D components
    _SDLRenderer = SDL_CreateRenderer(_SDLWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!_SDLRenderer) {
        logError("SDL Renderer could not be created.", 0);
        logSDLError();
        return;
    }

    _SDLGLContext = SDL_GL_CreateContext(_SDLWindow);
    SDL_GL_MakeCurrent(_SDLWindow, _SDLGLContext);

    // Vsync
    setVsync(1);

    if (SDL_SetRenderDrawBlendMode(_SDLRenderer, SDL_BLENDMODE_BLEND) < 0) logSDLError();

    // load Glad
    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0)
        logError("OpenGL could not initialized correctly. ", 0);
}

Window::~Window() {
    SDL_GL_DeleteContext(_SDLGLContext);
    SDL_DestroyWindow(_SDLWindow);
    SDL_DestroyRenderer(_SDLRenderer);
}

void Window::hide() {
    SDL_HideWindow(_SDLWindow);
}

void Window::show() {
    SDL_ShowWindow(_SDLWindow);
}

void Window::renderFrame() {
    SDL_GL_SwapWindow(_SDLWindow);
}

void Window::clearFrame() {
    int width = getWidth();
    int height = getHeight();

    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::setVsync(int interval) {
    if (interval != 1 && interval != -1 && interval != 0) return;

    if (SDL_GL_SetSwapInterval(interval))
        SDL_GL_SetSwapInterval(1);

    SDL_RenderSetVSync(_SDLRenderer, ((interval <= 0) ? interval : 0));
}

void Window::setBounds(int newWidth, int newHeight) {
    SDL_SetWindowSize(_SDLWindow, newWidth, newHeight);
    
    _width = newWidth;
    _height = newHeight;
}

void Window::setLocation(int x, int y) {
    SDL_SetWindowPosition(_SDLWindow, x, y);

    _location.x = x;
    _location.y = y;
}

bool Window::isVsyncOn() {
    return SDL_GL_GetSwapInterval() == 0 ? false : true;
}

glm::vec2 Window::getLocation() {
    return _location;
}

int Window::getWidth() {
    return _width;
}

int Window::getHeight() {
    return _height;
}

SDL_Window* Window::getSDLWindow() {
    return _SDLWindow;
}

SDL_Renderer* Window::getRenderer() {
    return _SDLRenderer;
}
