#include "Handler.h"

#include "Logger.h"
#include "Files.h"
#include "Physics.h"
#include "Timer.h"

#include "../util/gl/Shaders.h"
#include "../util/gl/Buffers.h"
#include "../util/gl/DefaultShaders.h"

#include <map>
#include <glad/glad.h>

namespace {
    std::multimap<unsigned int, unsigned int> layers; // layer, id
    std::map<unsigned int, Object*> objectMap; // id, object
    std::map<unsigned int, Shaders*> shaderMap; // id, shaders
    std::map<std::string, unsigned int> objectNames; // name, id
    std::map<std::string, Sprite*> savedSprites; // name, sprite

    Buffers* buffers;

    unsigned int updateTimerID;
}

void handler::init(const char* placeholderImagePath) {
    buffers = new Buffers(4, 6);

    saveSprite("placeholder", placeholderImagePath);

    updateTimerID = timer::createTimer();
}

unsigned int handler::createObject(unsigned int layer, const char* name, Object* object) {
    unsigned int id = objectMap.size();

    layers.insert(std::pair<unsigned int, unsigned int>(layers.size(), id));

    objectMap.insert(std::pair<unsigned int, Object*>(id, object));
    shaderMap.insert(std::pair<unsigned int, Shaders*>(id, new Shaders("", ""))); // use default shaders

    if (object->getAnimation() == nullptr)
        object->setAnimation(new Animation(savedSprites["placeholder"])); // static animation

    objectNames.insert(std::pair<std::string, unsigned int>(name, id));

    return id;
}

Object* handler::deleteObject(unsigned int id) {
    Object* object = objectMap[id];

    // delete id from layers
    for (auto it = layers.end(); it != layers.begin(); it--) {
        if (it->second == id) {
            layers.erase(it);
            break;
        }
    }

    delete objectMap[id];
    objectMap.erase(id);

    delete shaderMap[id];
    shaderMap.erase(id);

    return object;
}

Object* handler::getObject(unsigned int id) {
    Object* obj = objectMap[id];

    if (obj == nullptr) {
        logInfo("Object with ID " + std::to_string(id) + " not found.");
        return new Object();
    }

    return obj;
}

Object* handler::getObject(const char* name) {
    Object* obj = objectMap[objectNames[name]];

    if (obj == nullptr) {
        logInfo("Object with name " + std::string(name) + " not found.");
        return new Object();
    }

    return obj;
}

unsigned int handler::getObjectID(const char* name) {
    return objectNames[name];
}

void handler::setLayer(unsigned int id, unsigned int layer) {
    // delete id from layers
    for (auto it = layers.begin(); it != layers.end(); it++) {
        if (it->second == id) {
            layers.erase(it);
            break;
        }
    }

    layers.insert(std::pair<unsigned int, unsigned int>(layer, id));
}

void handler::drawAllObjects(int windowWidth, int windowHeight) {
    for (auto it = layers.begin(); it != layers.end(); it++) {
        Object* object = objectMap[it->second];
        Shaders* shaders = shaderMap[it->second];

        // update object
        object->events();
        object->update(timer::getTimeDiff(updateTimerID));

        if (object->isVisible() == false)
            continue;

        // activate texture
        if (object->getAnimation() != nullptr && !object->isAnimationsClosed())
            object->getAnimation()->step();

        // set shader uniforms
        shaders->activate();
        glm::mat4 model = object->getModelMatrix(windowWidth, windowHeight);
        shaders->setUniform("u_Model", (float*)&model, SHADER_MAT4);

        buffers->bind();
        buffers->setVertexData(object->getVertices(), object->getIndices());
        buffers->drawElements();
        buffers->unbind();

        // deactivate texture
        if (object->getAnimation() != nullptr && !object->isAnimationsClosed())
            object->getAnimation()->deactivate();
    }

    timer::resetTimer(updateTimerID);
}

void handler::changeShaders(unsigned int id, const char* vertexShaderSource, const char* fragmentShaderSource) {
    delete shaderMap[id];
    shaderMap[id] = new Shaders(vertexShaderSource, fragmentShaderSource);
}

void handler::saveSprite(const char* name, const char* path, bool flip) {
    savedSprites.insert(std::pair<std::string, Sprite*>(name, new Sprite(path, flip)));
}

Sprite* handler::getSprite(const char* name) {
    return savedSprites[name];
}
