
#include <iostream>
#include <string>

#include "Application.h"

#include "sys/Logger.h"
#include "sys/Events.h"
#include "sys/Handler.h"
#include "sys/Physics.h"

#include "Game/Game.h"

#include "util/Sprite.h"

#define NAME "Game"
#define VERSION "0.0.0"
#define LICENSE "MIT LICENSE: <https://www.mit.edu/~amini/LICENSE.md>"

bool debugMode;
bool quitEarly; 

/**
 * @brief Parse args (--help, --version, --debug)
 */
void parseArgs(char* args[]);

/**
 * @brief Starting location
 */
int main(int argc, char* args[]) {
	parseArgs(args);

	// if the --help or --version arguments are passed then application should not start
	if (quitEarly)
		return 0;

	// Initialize application
  	Application::initApp(NAME, VERSION, debugMode, 800, 600);
	handler::init("./data/images/placeholder.png");

	// Initialize game
	game::initSprites();
	game::initObjects();

	// Starting point of main loop
	while (!events::isQuitOccurred()) {
		events::fetchEvents();
		handler::drawAllObjects(WINDOW_WIDTH, WINDOW_HEIGHT);
		Application::operateFrame(0);
	}

	// Don't close terminal if -d argument passed
	if (Application::isDebugging())
    	system("pause");

	Application::destroyApp();

  	return 0;
}

/* Sources */

void parseArgs(char* args[]) {
  	for(const char *const *it = args + 1; *it; ++it) {
		std::string arg = *it;
		if(arg == "-h" || arg == "--help") {
			std::cerr <<  std::endl << "Command line arguments: " << std::endl;
			std::cerr << "  -h, --help: Prints help(this) message." << std::endl;
			std::cerr << "  -v, --version: Prints version info." << std::endl;
			std::cerr << "  -d, --debug: Enables debug mode." << std::endl;

			quitEarly = true;
		}

		else if(arg == "-v" || arg == "--version") {
			std::cerr << std::endl << NAME << " ver. "<< VERSION << std::endl << LICENSE << std::endl;
			quitEarly = true;
		}

		else if(arg == "-d" || arg == "--debug") {
      		debugMode = true;
			logger::setOutLogFile(false);
		}
	}
}
