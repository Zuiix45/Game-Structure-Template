#pragma once

#include "../headers.h"

class World : public Scene {
public:
    World();
    void update(double elapsedTime) override;
    void events() override;
private:
    unsigned int groundID;
};