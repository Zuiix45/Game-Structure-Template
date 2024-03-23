#include "Application.h"

#include "../sys/Logger.h"
#include "../sys/Engine.h"
#include "../sys/Events.h"
#include "../sys/Timer.h"
#include "../sys/TextRendering.h"

#include "../.Game/Player.h"

#define NAME "Game"
#define VERSION "0.0.0"
#define LICENSE "LICENSE"

#include <iostream>

bool debugMode;
/**
 * @brief Parse args (--help, --version, --debug)
 */
bool parseArgs(char* args[]);

void* operator new(size_t size) {
	void* p = malloc(size);

	std::cout << "Allocating " << size << " bytes at " << p << std::endl;

	return p;
}

/**
 * @brief Starting location
 */
int main(int argc, char* args[]) {
	// if the --help or --version arguments are passed then application should not start
	if (parseArgs(args)) return logger::enterBeforeClose();

	// Initialize application
  	App::initApp(NAME, VERSION, debugMode, 800, 600);
	engine::init("./data/images/");
	callbacks::init(App::getFocusedWindow()->getGLFWWindow());
	timer::init();
	fonts::init("./data/fonts/", "anta_regular", 32);

	// Stats panel
	unsigned int id = engine::registerObject(1, "stats_panel", make<Object>(ObjectType::HUD_ELEMENT, 0, 0, 300, 135, 0));
	engine::getObject(id)->closeAnimation();
	engine::getObject(id)->setAllColors(0, 0, 0, 0.5);
	engine::getObject(id)->setVisibility(false);

	// init game
	physics::setGravity(0.001f);

	unsigned int pid = engine::registerObject(1, "player", make<Player>(0, 0, 80, 80, 0.5));

	unsigned int aid = engine::registerObject(1, "a", make<Object>(ObjectType::OBJECT, 100, 100, 100, 100, 0));
	engine::getObject(aid)->setAllColors(255, 255, 255, 1);
	engine::getObject(aid)->closeAnimation();
	engine::getObject(aid)->effectByCamera(true);

	// Starting point of main loop
	while (App::isRunning()) {
		input::pollEvents();

		text::setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT); // remove
		engine::drawAllObjects();
		
		App::renderStats();
		App::operateFrame(0);

		benchmark::countFrames();
	}

	// Don't close terminal if -d argument passed
	if (App::isDebugging())
    	system("pause");

	fonts::destroy();
	App::destroyApp();

  	return 0;
}

/* Sources */

bool parseArgs(char* args[]) {
  	for(const char *const *it = args + 1; *it; ++it) {
		std::string arg = *it;
		if(arg == "-h" || arg == "--help") {
			logger::printHelp();
			return true;
		}

		else if(arg == "-v" || arg == "--version") {
			logger::printVersion(NAME, VERSION, LICENSE);
			return true;
		}

		else if(arg == "-d" || arg == "--debug") {
      		debugMode = true;
			logger::setOutLogFile(false);
		}
	}

	return false;
}
