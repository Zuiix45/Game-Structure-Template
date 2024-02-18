#include "Engine.h"

#include "Logger.h"
#include "Files.h"
#include "Physics.h"
#include "Timer.h"
#include "LuaBinder.h"

#include "../util/gl/Shaders.h"
#include "../util/gl/Buffers.h"
#include "../util/gl/DefaultShaders.h"

#include <map>
#include <memory>
#include <glad/glad.h>

/**
 * @brief This Struct is used to store the object's data.
 * 
 */
struct Container {
    std::unique_ptr<Object> object = nullptr;
    std::unique_ptr<Shaders> shaders = nullptr;
    std::unique_ptr<Animation> animation = nullptr;
    std::vector<const char*> scripts;
    bool isAnimationClosed;
};

namespace {
    std::multimap<unsigned int, unsigned int> layers; // layer, container id
    std::map<unsigned int, std::unique_ptr<Container>> containers; // id, container
    std::map<const char*, unsigned int> containerToId; // name, container id
    std::map<unsigned int, const char*> idToContainer; // container id, name
    
    std::map<const char*, const char*> spritePaths; // name, path

    Buffers* buffers;

    unsigned int updateTimerID;
}

void engine::init(const char* imagesPath) {
    buffers = new Buffers(4, 6); // 4 vertex, 6 index

    // load all sprites
    std::vector<std::string> files = files::getAllFilePaths(imagesPath);

    for (auto& path : files) {
        std::string name = files::extractFileName(path);
        spritePaths.insert(std::pair<const char*, const char*>(name.c_str(), path.c_str()));
    }

    updateTimerID = timer::createTimer();
}

unsigned int engine::createContainer(unsigned int layer, const char* name) {
    unsigned int id = containers.size();

    containers.insert(std::pair<unsigned int, std::unique_ptr<Container>>(id, std::make_unique<Container>()));
    layers.insert(std::pair<unsigned int, unsigned int>(layer, id));
    containerToId.insert(std::pair<const char*, unsigned int>(name, id));
    idToContainer.insert(std::pair<unsigned int, const char*>(id, name));

    containers[id]->object = std::make_unique<Object>();
    containers[id]->shaders = std::make_unique<Shaders>("", ""); // use default shaders
    containers[id]->isAnimationClosed = false;

    if (containers[id]->animation == nullptr)
        containers[id]->animation = std::make_unique<Animation>(convertSprite("placeholder")); // static placeholder animation

    return id;
}

void engine::deleteContainer(unsigned int id) {
    // delete id from layers
    for (auto it = layers.end(); it != layers.begin(); it--) {
        if (it->second == id) {
            layers.erase(it);
            break;
        }
    }

    containerToId.erase(idToContainer[id]);
    idToContainer.erase(id);
    containers.erase(id);
}

void engine::setLayer(unsigned int id, unsigned int layer) {
    // delete id from layers
    for (auto it = layers.begin(); it != layers.end(); it++) {
        if (it->second == id) {
            layers.erase(it);
            break;
        }
    }

    layers.insert(std::pair<unsigned int, unsigned int>(layer, id));
}

void engine::drawAll(int windowWidth, int windowHeight) {
    for (auto& it : layers) {
        unsigned int id = it.second;

        // run scripts
        for (const char* scriptName : containers[id]->scripts)
            lua::runScript(scriptName);

        if (containers[id]->object->isVisible() == false)
            continue;

        // activate texture
        if (containers[id]->animation != nullptr && !containers[id]->isAnimationClosed)
            containers[id]->animation->step();

        // set shader uniforms
        containers[id]->shaders->activate();
        glm::mat4 model = containers[id]->object->getModelMatrix(windowWidth, windowHeight);
        containers[id]->shaders->setUniform("u_Model", (float*)&model, SHADER_MAT4);

        buffers->bind();
        buffers->setVertexData(containers[id]->object->getVertices(), containers[id]->object->getIndices());
        buffers->drawElements();
        buffers->unbind();

        // deactivate texture
        if (containers[id]->animation != nullptr && !containers[id]->isAnimationClosed)
            containers[id]->animation->deactivate();
    }

    timer::resetTimer(updateTimerID);
}

void engine::closeAnimations(unsigned int id) {
    containers[id]->isAnimationClosed = true;
    containers[id]->shaders = std::make_unique<Shaders>(defaultVertexShaderSource, defaultNoTextureFragmentShaderSource);
}

void engine::changeShaders(unsigned int id, const char* vertexShaderSource, const char* fragmentShaderSource) {
    containers[id]->shaders = std::make_unique<Shaders>(vertexShaderSource, fragmentShaderSource);
}

const char* engine::getSpritePath(const char* name) {
    return spritePaths[name];
}

void engine::bindScriptToContainer(unsigned int id, const char* scriptName) {
    containers[id]->scripts.push_back(scriptName);
}

std::vector<const char*> engine::convertSprite(const char* spriteName) {
    std::vector<const char*> result;
    result.push_back(spriteName);
    return result;
}