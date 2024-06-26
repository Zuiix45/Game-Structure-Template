#include "Application.h"

#include "../sys/Logger.h"
#include "../sys/Timer.h"
#include "../sys/Engine.h"
#include "../sys/Events.h"
#include "../sys/Events.h"
#include "../sys/TextRendering.h"

#include <algorithm>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// Static variables

int App::sessionTimer;
int App::frameTimer;
double App::checkPoint;
int App::currentFPS;
int App::lastFPS ;
const char* App::_name;
const char* App::_version;
bool App::_debugMode;
bool App::isInitSuccess;
bool App::showStats;
std::shared_ptr<Window> App::focusedWindow;
GLenum App::currentError;

namespace {
    /**
     * @brief Parse args (--help, --version, --debug)
     */
    bool parseArgs(char* args[], bool& debugMode, const char* name, const char* version) {
        for(const char *const *it = args + 1; *it; ++it) {
            std::string arg = *it;
            if(arg == "-h" || arg == "--help") {
                logger::printHelp();
                return true;
            }

            else if(arg == "-v" || arg == "--version") {
                logger::printVersion(name, version);
                return true;
            }

            else if(arg == "-d" || arg == "--debug") {
                debugMode = true;
                logger::setOutLogFile(false);
            }
        }

        return false;
    }
}

/* Implementation of Application class */

bool App::initApp(const char* name, const char* version, 
            int width, int height, const char* resourcesFolderPath, 
            const char* defaultFontName, int defaultFontSize, char* args[]) {

    if (isInitSuccess) return true;

    if (parseArgs(args, _debugMode, name, version)) return true;

    _name = name;
    _version = version;

    showStats = false;

    // Initialize SDL
	if (glfwInit() != GLFW_TRUE) return false;

    // Set error callback
    glfwSetErrorCallback([](int error, const char* description) {
        logError(description, error);
    });

    // SDL Attributes
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, GL_FALSE);

    // Create the main window for application
    #ifdef _WIN32
        SetProcessDPIAware();
    #endif
    
    focusedWindow = std::make_shared<Window>(name, width, height);

    if (!focusedWindow) return false;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // initialize modules
    input::init(focusedWindow->getGLFWWindow());
    timer::init();
    fonts::init(std::string(resourcesFolderPath) + "fonts", defaultFontName, defaultFontSize);
	engine::init(std::string(resourcesFolderPath) + "images");

    // Create timers
    sessionTimer = timer::createTimer();
    frameTimer = timer::createTimer();

    currentFPS = 0;
    lastFPS = 0;
    checkPoint = 0;

    // Stats panel - semi-transparent background of stats
	unsigned int statsPanelID = engine::registerObject("stats_panel", make<Object>(ObjectType::HUD_ELEMENT, 0, 0, 300, 135, 0));
	engine::getObject(statsPanelID)->closeAnimation();
	engine::getObject(statsPanelID)->setAllColors(0, 0, 0, 0.5);
	engine::getObject(statsPanelID)->setVisibility(false);
    
    return isInitSuccess; // Initialization was successful
}

void App::destroyApp() {
    fonts::destroy();

    timer::killTimer(sessionTimer);
    timer::killTimer(frameTimer);

    isInitSuccess = false;

    glfwTerminate();
}

const char* App::getAppName() {
    return _name;
}

const char* App::getVersion() {
    return _version;
}

bool App::isDebugging() {
    return _debugMode;
}

bool App::isRunning() {
    return !glfwWindowShouldClose(focusedWindow->getGLFWWindow());
}

double App::getSessionTime() {
    return timer::getTimeDiff(sessionTimer);
}

int App::getFPS() {
    return lastFPS;
}

void App::startLoop(int fpsCap) {
    while (isRunning()) {
        // fetch events
        input::pollEvents();

        // update and draw objects
        engine::drawAllObjects();
        App::drawStats();

        // Render newly created frame
        focusedWindow->renderFrame();

        // update frame count of last second
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

        // Check if an OpenGL error occurred
        GLenum newError = glGetError();
        if (newError != currentError) logError("OpenGL error occurred", newError);
        currentError = newError;

        // Benchmark
        benchmark::countFrames();
    }
}

void App::changeFocus(std::shared_ptr<Window> newWindow) {
    focusedWindow = newWindow;
}

std::shared_ptr<Window> App::getFocusedWindow() {
    return focusedWindow;
}

void App::drawStats() {
    if (!showStats) return;
    
    text::setRendererColor(0.0f, 255.0f, 0.0f);
    text::setRendererScale(0.5f);
    text::setRendererX(10.0f);
    text::setRendererY(10.0f);

    text::renderText(DEF_FONT, "FPS: " + std::to_string(lastFPS));

    text::setRendererY(30.0f);
    std::string avg = benchmark::applyPrecision(benchmark::getAverageFrameTime(), 3);
    text::renderText(DEF_FONT, "Average Frame Time: " + avg + "ms");

    text::setRendererY(50.0f);
    text::renderText(DEF_FONT, "Session Time: " + std::to_string((int)(getSessionTime()/1000)) + "s");

    text::setRendererY(70.0f);
    std::string benchmark = benchmark::applyPrecision(benchmark::getBenchmarkResult(), 3);
    text::renderText(DEF_FONT, "Last Benchmark Result: " + benchmark + "ms");

    text::setRendererY(90.0f);
    std::string lastFrameDuration = benchmark::applyPrecision(benchmark::getLastFrameDuration(), 3);
    text::renderText(DEF_FONT, "Last Frame Duration: " + lastFrameDuration + "ms");

    text::setRendererY(110.0f);
    text::renderText(DEF_FONT, "Object Count: " + std::to_string(engine::getTotalObjectCount()-1)); // don't count stats panel
}

bool App::isShowingStats() {
    return showStats;
}
void App::toggleStats() {
    showStats = !showStats;
    engine::getObject(engine::getObjectID("stats_panel"))->setVisibility(showStats);
}
