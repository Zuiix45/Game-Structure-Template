#include "Sprite.h"

#include "../sys/Files.h"
#include "../sys/Logger.h"

#include <glad/glad.h>

Sprite::Sprite(const char* imagePath, bool flip) {
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture from file
    Image loadedTexture = files::loadImage(imagePath, flip);

    if (loadedTexture.data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedTexture.width, loadedTexture.height, 0, 
                    loadedTexture.nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, loadedTexture.data);

        textureID = texture;
        isLoaded = true;
    }
    
    else {
        logError("Failed to load texture: " + loadedTexture.path, 0);
        isLoaded = false;
    }
    
    loadedTexture.free();
}

Sprite::~Sprite() {
    glDeleteTextures(1, &textureID);
}

void Sprite::activateTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Sprite::deactivateTexture() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Sprite::getTextureID() const {
    return textureID;
}

bool Sprite::isLoadedSuccessfully() const {
    return isLoaded;
}

/////////////////

Animation::Animation(Sprite* frame) {
    if (!frame->isLoadedSuccessfully()) {
        logError("Failed to load animation", 0);
        isLoaded = false;
        return;
    }

    this->fps = 0;
    this->frameTime = 0.0f;
    currentKeyframe = 0;

    animTimerID = timer::createTimer();

    keyframes.push_back(frame);

    isLoaded = true;
}

Animation::Animation(std::vector<Sprite*> keyframes, int fps, float speed) {
    for (Sprite* keyframe : keyframes) {
        if (!keyframe->isLoadedSuccessfully()) {
            logError("Failed to load animation", 0);
            isLoaded = false;
            return;
        }
    }

    this->keyframes = keyframes;
    this->fps = fps;
    currentKeyframe = 0;

    animTimerID = timer::createTimer();

    frameTime = 1000.0f / fps / speed;
    
    isLoaded = true;
}

void Animation::step() {
    if (isLoaded == false) return;
    if (keyframes.size() == 0) return;
    if (keyframes.size() == 1) {
        keyframes[0]->activateTexture();
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

    keyframes[currentKeyframe]->activateTexture();
}

void Animation::deactivate() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Animation::isLoadedSuccessfully() const {
    return isLoaded;
}
