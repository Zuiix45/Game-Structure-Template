#include "Sprite.h"

#include "../sys/Files.h"
#include "../sys/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

Sprite::Sprite(const char* firstTexturePath, bool flip) {
    addTexture(firstTexturePath);
}

void Sprite::addTexture(const char* path, bool flip) {
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);

    std::string normalizedPath = files::normalizePath(path);
    
    unsigned char *data = stbi_load(normalizedPath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        logError("Failed to load texture: " + normalizedPath, 0);

    stbi_image_free(data);

    textures.push_back(texture);
}

void Sprite::deleteTexture(unsigned int index) {
    glDeleteTextures(1, &textures[index]);
    textures.erase(textures.begin() + index);
}

int Sprite::getTextureCount() const {
    return textures.size();
}

void Sprite::activateTextures() const {
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
}
