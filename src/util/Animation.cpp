#include "Animation.h"

#include "../sys/Files.h"
#include "../sys/Logger.h"
#include "../sys/Engine.h"
#include "../sys/Timer.h"

#include <glad/glad.h>

namespace {
    bool loadSprite(const char* imagePath, unsigned int* spriteID) {
        unsigned int sprite;

        glGenTextures(1, &sprite);
        glBindTexture(GL_TEXTURE_2D, sprite);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load sprite from file
        Image loadedSprite = files::loadImage(imagePath);

        if (loadedSprite.data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSprite.width, loadedSprite.height, 0, 
                        loadedSprite.nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, loadedSprite.data);

            spriteID = &sprite;
        }
        
        else {
            logError("Failed to load Sprite: " + loadedSprite.path, 0);
            return false;
        }
        
        loadedSprite.free();

        return true;
    }
}

/////////////////

Animation::Animation(std::vector<const char*> keyframeNames, int fps, float speed) {
    for (auto spriteName : keyframeNames) {
        unsigned int spriteID;

        if (!loadSprite(engine::getSpritePath(spriteName), &spriteID)) {
            logError("Failed to load animation", 0);
            isLoaded = false;
            return;
        }

        keyframes.push_back(spriteID);
    }

    this->fps = fps;
    currentKeyframe = 0;

    animTimerID = timer::createTimer();

    if (fps == 0 || speed == 0.0f) { frameTime = 0.0f; }
    else { frameTime = 1000.0f / fps / speed; }
    
    isLoaded = true;
}

Animation::~Animation() {
    timer::killTimer(animTimerID);

    for (unsigned int i = 0; i < keyframes.size(); i++) {
        glDeleteTextures(1, &keyframes[i]);
    }

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
