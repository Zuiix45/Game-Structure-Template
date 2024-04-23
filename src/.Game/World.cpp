#include "World.h"

World::World() {
    groundID = engine::registerObject("ground", make<Entity>(0, 0, 800, 50));
    engine::getObject(groundID)->closeAnimation();
    engine::setObjectColor(groundID, 50, 100, 60);

    addOBject(1, groundID);
}

void World::update(double elapsedTime) {
    engine::getCamera()->setXOffset(0);
    engine::getCamera()->setYOffset(WINDOW_HEIGHT/2 + 50);

    engine::getCamera()->follow(groundID);
}

void World::events() {

}
