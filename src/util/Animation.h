#pragma once

#include <vector>
#include <string>

class Animation {
public:
    Animation(int fps = 24, float speed = 1.0f);
    ~Animation();

    void calculateFrameTime(int fps, float speed);

    void setKeyFrames(std::vector<unsigned int> newKeyframes);
    void loadKeyFrames(std::vector<std::string> spriteNames, bool flip = true);

    void step();
    void deactivate();

    bool isLoadedSuccessfully() const;

private:
    std::vector<unsigned int> keyframes;

    int currentKeyframe;
    double frameTime;

    bool isLoaded;

    unsigned int animTimerID;
};
