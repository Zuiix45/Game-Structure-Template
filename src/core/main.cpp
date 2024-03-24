#include "Application.h"

#include "../sys/Logger.h"
#include "../sys/Engine.h"
#include "../sys/Events.h"
#include "../sys/Timer.h"
#include "../sys/TextRendering.h"

#include "../.Game/definitions.h"

#include "../.Game/Player.h"

#include <iostream>

bool debugMode;
/**
 * @brief Parse args (--help, --version, --debug)
 */
bool parseArgs(char* args[]);

void* operator new(size_t size) {
	void* p = malloc(size);

	//std::cout << "Allocating " << size << " bytes at " << p << std::endl; // -- open this line for allocation tracking

	return p;
}

/**
 * @brief Starting location
 */
int main(int argc, char* args[]) {
	// if the --help or --version arguments are passed then application should not start
	if (parseArgs(args)) return logger::enterBeforeClose();

	// Initialize application
  	App::initApp(NAME, VERSION, debugMode, SCREEN_WIDTH, SCREEN_HEIGHT);
	callbacks::init(App::getFocusedWindow()->getGLFWWindow());
	timer::init();
	fonts::init(FONTS_PATH, DEFAULT_FONT, DEFAULT_FONT_SIZE);
	engine::init(IMAGES_PATH);

	// Stats panel - semi-transparent background of stats
	unsigned int id = engine::registerObject(1, "stats_panel", make<Object>(ObjectType::HUD_ELEMENT, 0, 0, 300, 135, 0));
	engine::getObject(id)->closeAnimation();
	engine::getObject(id)->setAllColors(0, 0, 0, 0.5);
	engine::getObject(id)->setVisibility(false);

	// init game
	physics::setGravity(0.001f);

	unsigned int pid = engine::registerObject(1, "player", make<Player>(0, 0, 80, 80, 0.5));

	unsigned int aid = engine::registerObject(2, "a", make<Object>(ObjectType::OBJECT, 100, 100, 100, 100, 0));
	engine::getObject(aid)->setAllColors(255, 255, 255, 1);
	engine::getObject(aid)->closeAnimation();
	engine::getObject(aid)->effectByCamera(true);

	// Starting point of main loop
	while (App::isRunning()) {
		input::pollEvents();

		engine::drawAllObjects();
		App::drawStats();

		App::operateFrame(0);

		benchmark::countFrames();
	}

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
