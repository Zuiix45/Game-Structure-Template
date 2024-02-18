#pragma once

#include <vector>

class Animation {
public:
    Animation(std::vector<const char*> keyframeNames, int fps=24, float speed=1.0f);
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
