#pragma once

#include "../sys/Handler.h"

#include "Player.h"
#include "Barrier.h"

#include <string>

#define PLAYER_LAYER 1
#define BARRIER_LAYER 2

namespace game {
    void initSprites() {
        std::string defPath = "./data/images/";

        handler::saveSprite("playerUp", (defPath + "playerUp.png").c_str());
        handler::saveSprite("playerDown", (defPath + "playerDown.png").c_str());
        handler::saveSprite("playerLeft", (defPath + "playerLeft.png").c_str());
        handler::saveSprite("playerRight", (defPath + "playerRight.png").c_str());
    }

    void initObjects() {
        handler::createObject(PLAYER_LAYER, "player", new Player());
        handler::createObject(BARRIER_LAYER, "barrier", new Barrier(100, 100, 100, 100));
    }
}