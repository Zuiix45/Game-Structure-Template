#pragma once

#include "../sys/Handler.h"

#include "Player.h"

#include <string>

#define PLAYER_LAYER 1

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
    }
}