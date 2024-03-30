#include "headers.h"

#include ".Game/Player.h"
#include ".Game/World.h"

int main(int argc, char* args[]) {
	// Initialize application
  	App::initApp("Game", "0.0.0", 800, 600, "./res/", "anta_regular", 32, args);

	// init game
	cast<World> world = make<World>();

	physics::setGravity(0.001f);

	cast<Player> playerObject = make<Player>(0, 0, 80, 80, 0.5);
	unsigned int playerID = engine::registerObject("player", playerObject);

	unsigned int aid = engine::registerObject("a", make<Object>(ObjectType::OBJECT, 100, 100, 100, 100, 0));
	engine::getObject(aid)->setAllColors(255, 255, 255, 1);
	engine::getObject(aid)->closeAnimation();
	engine::getObject(aid)->effectByCamera(true);

	world->addOBject(1, playerID);
	world->addOBject(2, aid);
	
	App::startLoop(0);

	App::destroyApp();

  	return 0;
}

