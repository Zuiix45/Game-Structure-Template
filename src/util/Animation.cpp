#include "Animation.h"

#include "../sys/Files.h"
#include "../sys/Logger.h"
#include "../sys/Engine.h"
#include "../sys/Timer.h"

#include <glad/glad.h>

Animation::Animation(int fps, float speed) {
    calculateFrameTime(fps, speed);

    currentKeyframe = 0;
    animTimerID = timer::createTimer();
    isLoaded = false;
}

Animation::~Animation() {
    for (auto& keyframe : keyframes) glDeleteTextures(1, &keyframe);
}

void Animation::calculateFrameTime(int fps, float speed) {
    frameTime = 1000.0f / fps / speed;
}

void Animation::setKeyFrames(std::vector<unsigned int> newKeyframes) {
    keyframes = newKeyframes;
    isLoaded = true;
}

void Animation::loadKeyFrames(std::vector<std::string> spriteNames, bool flip) {
    for (auto& name : spriteNames) {
        std::string path = engine::getSpritePath(name);

        unsigned int spriteID;

        glGenTextures(1, &spriteID);
        glBindTexture(GL_TEXTURE_2D, spriteID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load image from file
        Image loadedSprite = files::loadImage(path, flip);

        if (!loadedSprite.isLoaded) {
            logError("Failed to load sprite: " + name, SPRITE_LOADING_ERROR);
            isLoaded = false;
            return;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSprite.width, loadedSprite.height, 0, 
            loadedSprite.nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, loadedSprite.data);

        if (!loadedSprite.data) {
            logError("Failed to load sprite: " + name, SPRITE_LOADING_ERROR);
            isLoaded = false;
            return;
        }

        keyframes.push_back(spriteID);

        loadedSprite.free();
    }

    isLoaded = true;
}


void Animation::step() {
    if (isLoaded == false) return;
    if (keyframes.size() == 0) return;
    if (keyframes.size() == 1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, keyframes[0]);
        return;
    }

    double timeDiff = timer::getTimeDiff(animTimerID);

    if (timeDiff >= frameTime) {
        currentKeyframe++;
        timer::resetTimer(animTimerID);
    }

    if (currentKeyframe >= keyframes.size()) {
        currentKeyframe = 0;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, keyframes[currentKeyframe]);
}

void Animation::deactivate() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Animation::isLoadedSuccessfully() const {
    return isLoaded;
}
