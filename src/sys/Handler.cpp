#include "Handler.h"

#include "../util/gl/Shaders.h"
#include "../util/gl/Buffers.h"

#include <map>

namespace {
    std::multimap<unsigned int, unsigned int> layers; // layer, id
    std::map<unsigned int, Object*> objectMap; // id, object
    std::map<unsigned int, Shaders*> shaderMap; // id, shaders

    Buffers* buffers;
}

void handler::init() {
    buffers = new Buffers(4, 6);
}

unsigned int handler::createObject(unsigned int layer, Object* object) {
    unsigned int id = objectMap.size();

    layers.insert(std::pair<unsigned int, unsigned int>(layer, id));

    objectMap.insert(std::pair<unsigned int, Object*>(id, object));
    shaderMap.insert(std::pair<unsigned int, Shaders*>(id, new Shaders("", ""))); // render object with default shaders

    return id;
}

Object* handler::deleteObject(unsigned int id) {
    Object* object = objectMap[id];

    // delete id from layers
    for (auto it = layers.begin(); it != layers.end(); it++) {
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
    for (auto it = layers.begin(); it != layers.end(); it++) {
        Object* object = objectMap[it->second];
        Shaders* shaders = shaderMap[it->second];

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
