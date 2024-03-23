#include "Engine.h"

#include "Logger.h"
#include "Files.h"
#include "Physics.h"
#include "Timer.h"

#include "../util/renderer/Shaders.h"
#include "../util/renderer/Buffers.h"
#include "../util/renderer/DefaultShaders.h"

#include "../classes/Entity.h"
#include "../classes/SubEntity.h"
#include "../classes/NonEntity.h"

#include "../core/Application.h"

#include <map>
#include <glad/glad.h>

namespace {
    std::multimap<unsigned int, unsigned int> layers; // layer, object id
    std::map<unsigned int, cast<Object>> objectMap; // object id, object pointer
    std::map<std::string, unsigned int> nameToID; // name, object id
    std::map<unsigned int, std::string> idToName; // object id, name
    std::map<std::string, std::string> savedSpritePaths; // name, path

    std::vector<std::shared_ptr<Buffers>> bufferList;

    std::shared_ptr<Camera> mainCamera;
}

void engine::init(const char* imagesPath) {
    // TODO: add other buffer types
    bufferList.push_back(std::make_shared<Buffers>(4, 6)); // filled rectangular buff
    bufferList.push_back(std::make_shared<Buffers>(4, 8)); // empty rectangular buff
    
    // load all sprites
    std::vector<std::string> allPaths = files::getAllFilePaths(imagesPath);

    for (auto& path : allPaths) {
        std::string nPath = files::normalizePath(path);
        std::string name = files::extractFileName(nPath);
        name = name.substr(0, name.find_last_of("."));
        savedSpritePaths.insert(std::pair<std::string, std::string>(name, nPath));
    }

    // create default camera
    mainCamera = std::make_shared<Camera>(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f);
}

unsigned int engine::registerObject(unsigned int layer, const std::string& objName, cast<Object> object) {
    unsigned int objID = objectMap.size() + 1;// create unique id
    layers.insert(std::pair<unsigned int, unsigned int>(layer, objID));

    objectMap.insert(std::pair<unsigned int, cast<Object>>(objID, object));

    if (!object->isAnimationValid())
        object->loadAnimation(convertSpriteNameToList("placeholder"), 24, 1.0f, true); // static animation

    nameToID.insert(std::pair<std::string, unsigned int>(objName, objID));
    idToName.insert(std::pair<unsigned int, std::string>(objID, objName));

    object->setID(objID);

    return objID;
}

std::shared_ptr<Buffers> engine::getBuffers(unsigned int bufferType) {
    return bufferList[bufferType];
}

unsigned int engine::getTotalObjectCount() { return objectMap.size(); }

cast<Object> engine::getObject(unsigned int objID) {
    return objectMap[objID];
}

unsigned int engine::getObjectID(const std::string& objName) {
    return nameToID[objName];
}

std::string engine::getObjectName(unsigned int objID) {
    return idToName[objID];
}

void engine::drawAllObjects() {
    // calculate view matrix
    mainCamera->calculateViewMatrix();

    // reverse iterate through layers, so that the last(lower value) layer is drawn firsts
    for (auto i = layers.rbegin(); i != layers.rend(); i++) {
        auto obj = objectMap[i->second];
        
        switch (obj->getType()) {
            case ObjectType::ENTITY: {
                cast<Entity> entity = std::dynamic_pointer_cast<Entity>(obj);
                entity->events();
                entity->update(entity->getElapsedTime());
                break;
            }

            case ObjectType::SUB_ENTITY: {
                cast<SubEntity> subEntity = std::dynamic_pointer_cast<SubEntity>(obj);
                subEntity->events();
                subEntity->update(subEntity->getElapsedTime());
                break;
            }
            
            case ObjectType::NON_ENTITY: {
                cast<NonEntity> nonEntity = std::dynamic_pointer_cast<NonEntity>(obj);
                nonEntity->events();
                break;
            }
        }

        obj->draw(App::getFocusedWindow(), mainCamera);
    }
}

std::string engine::getSpritePath(const std::string& spriteName) {
    return savedSpritePaths[spriteName];
}

std::vector<std::string> engine::convertSpriteNameToList(const std::string& spriteName) {
    std::vector<std::string> result;
    result.push_back(spriteName);
    return result;
}

void engine::setCamera(cast<Camera> camera) { mainCamera = camera; }
cast<Camera> engine::getCamera() { return mainCamera; }
