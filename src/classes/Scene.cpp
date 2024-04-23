#include "Scene.h"

#include "../sys/Timer.h"

Scene::Scene() {
    loopTimer = timer::createTimer();
}

double Scene::getFrameTime() {
    auto elapsedTime = timer::getTimeDiff(loopTimer);
    timer::resetTimer(loopTimer);
    return elapsedTime;
}

void Scene::addOBject(unsigned int layer, unsigned int objID) {
    renderingQueue.insert(std::pair<unsigned int, unsigned int>(layer, objID));
}

std::multimap<unsigned int, unsigned int> Scene::getRenderingQueue() {
    return renderingQueue;
}
