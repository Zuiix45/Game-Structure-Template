#include "headers.h"

#include ".Game/Player.h"

int main(int argc, char* args[]) {
	// Initialize application
  	App::initApp("Game", "0.0.0", 800, 600, "./res/", "anta_regular", 32, args);

	// init game
	
	App::startLoop(0);

	App::destroyApp();

  	return 0;
}

