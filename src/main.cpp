#include "headers.h"

#include ".Game/Player.h"

int main(int argc, char* args[]) {
	// Initialize application
  	App::initApp("Game", "0.0.0", 800, 600, "./res/", "anta_regular", 32, args);

	// init game
	physics::setGravity(0.001f);

	unsigned int pid = engine::registerObject(1, "player", make<Player>(0, 0, 80, 80, 0.5));

	unsigned int aid = engine::registerObject(2, "a", make<Object>(ObjectType::OBJECT, 100, 100, 100, 100, 0));
	engine::getObject(aid)->setAllColors(255, 255, 255, 1);
	engine::getObject(aid)->closeAnimation();
	engine::getObject(aid)->effectByCamera(true);
	
	App::startLoop(0);

	App::destroyApp();

  	return 0;
}

