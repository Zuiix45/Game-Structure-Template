#pragma once

#include "../classes/Scene.h"

class World : public Scene {
public:
    World();
    void update(double elapsedTime) override;
    void events() override;
};