#include "Handler.h"

#include "Logger.h"
#include "Files.h"
#include "Physics.h"

#include "../util/gl/Shaders.h"
#include "../util/gl/Buffers.h"
#include "../util/gl/DefaultShaders.h"

#include <map>
#include <glad/glad.h>

namespace {
    std::multimap<unsigned int, unsigned int> layers; // layer, id
    std::map<unsigned int, Object*> objectMap; // id, object
    std::map<unsigned int, Shaders*> shaderMap; // id, shaders
    std::map<std::string, Sprite*> savedSprites; // name, sprite

    Buffers* buffers;
}

void handler::init(const char* placeholderImagePath) {
    buffers = new Buffers(4, 6);

    saveSprite("placeholder", placeholderImagePath);
}

unsigned int handler::createObject(unsigned int layer, Object* object) {
    unsigned int id = objectMap.size();

    layers.insert(std::pair<unsigned int, unsigned int>(layers.size(), id));

    objectMap.insert(std::pair<unsigned int, Object*>(id, object));
    shaderMap.insert(std::pair<unsigned int, Shaders*>(id, new Shaders("", ""))); // use default shaders

    object->setAnimation(new Animation(savedSprites["placeholder"]));

    return id;
}

Object* handler::deleteObject(unsigned int id) {
    Object* object = objectMap[id];

    for (int i = 0; i < object->getHitBoxIDs().size(); i++) {
        physics::destroyHitBox(object->getHitBoxIDs()[i]);
    }

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
    return objectMap[id];
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
    physics::checkCollisions();

    for (auto it = layers.begin(); it != layers.end(); it++) {
        Object* object = objectMap[it->second];
        Shaders* shaders = shaderMap[it->second];

        if (object->isVisible() == false)
            continue;

        // activate texture
        object->getAnimation()->step();

        // set shader uniforms
        shaders->activate();
        glm::mat4 model = object->getModelMatrix(windowWidth, windowHeight);
        shaders->setUniform("u_Model", (float*)&model, SHADER_MAT4);

        buffers->bind();
        buffers->setVertexData(object->getVertices(), object->getIndices());
        buffers->drawElements();
        buffers->unbind();
    }
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
