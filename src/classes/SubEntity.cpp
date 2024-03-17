#include "SubEntity.h"

SubEntity::SubEntity() : Object(ObjectType::SUB_ENTITY) {
    loopTimer = timer::createTimer();
}

double SubEntity::getElapsedTime() {
    auto elapsedTime = timer::getTimeDiff(loopTimer);
    timer::resetTimer(loopTimer);
    return elapsedTime;
}