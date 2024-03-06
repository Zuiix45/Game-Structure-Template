#pragma once

#include <vector>
#include <string>

class Animation {
public:
    Animation(std::vector<std::string> spriteNames, int fps = 24, float speed = 1.0f, bool flip = true);
    ~Animation();

    void step();
    void deactivate();

    bool isLoadedSuccessfully() const;

private:
    std::vector<unsigned int> keyframes;

    int fps;
    int currentKeyframe;
    double frameTime;

    bool isLoaded;

    unsigned int animTimerID;
};
