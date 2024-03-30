#include "Scene.h"

Scene::Scene() {
    loopTimer = 0;
}

double Scene::getFrameTime() {
    return loopTimer;
}

void Scene::addOBject(unsigned int layer, unsigned int objID) {
    renderingQueue.insert(std::pair<unsigned int, unsigned int>(layer, objID));
}

std::multimap<unsigned int, unsigned int> Scene::getRenderingQueue() {
    return renderingQueue;
}
