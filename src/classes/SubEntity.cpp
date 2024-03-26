#include "SubEntity.h"

SubEntity::SubEntity() : Object(ObjectType::SUB_ENTITY) {
    loopTimer = timer::createTimer();

    effectByCamera(true); // all sub entities are affected by camera
}

double SubEntity::getFrameTime() {
    auto elapsedTime = timer::getTimeDiff(loopTimer);
    timer::resetTimer(loopTimer);
    return elapsedTime;
}
