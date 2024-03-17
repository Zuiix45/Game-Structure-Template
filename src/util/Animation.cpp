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
    looping = false;
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
        std::string path = engine::getSpritePath(name); // get sprite path from saved paths

        unsigned int spriteID;

        // generate texture id
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

        // create texture from image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSprite.width, loadedSprite.height, 0, 
            loadedSprite.nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, loadedSprite.data);

        if (!loadedSprite.data) {
            logError("Failed to load sprite: " + name, SPRITE_LOADING_ERROR);
            isLoaded = false;
            return;
        }

        // add texture id to keyframes
        keyframes.push_back(spriteID);

        // we don't need the image data anymore
        loadedSprite.free();
    }

    isLoaded = true;
}


void Animation::step() {
    if (isLoaded == false) return;
    if (keyframes.size() == 0) return;
    if (keyframes.size() == 1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, keyframes[0]); // bind the only key frame
        return;
    }

    double timeDiff = timer::getTimeDiff(animTimerID);

    // if the time difference is greater than the frame time, move to the next key frame
    if (timeDiff >= frameTime) {
        currentKeyframe++;
        timer::resetTimer(animTimerID);
    }

    // restart or stop the animation if it has reached the end
    if (currentKeyframe >= keyframes.size()) {
        if (looping) {
            currentKeyframe = 0; // restart if looping
        } else {
            currentKeyframe = keyframes.size() - 1;
            finished = true;
        }
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, keyframes[currentKeyframe]); // bind the current key frame
}

void Animation::deactivate() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Animation::loop() { looping = true; }
void Animation::stop() { looping = false; }

void Animation::reset() {
    currentKeyframe = 0;
    finished = false;
}

bool Animation::isLooping() const { return looping; }
bool Animation::isFinished() const { return finished; }
bool Animation::isLoadedSuccessfully() const { return isLoaded; }
