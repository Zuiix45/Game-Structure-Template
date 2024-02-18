#include "LuaBinder.h"

#include "Timer.h"
#include "Engine.h"
#include "Logger.h"
#include "Files.h"

#include <map>

namespace {
    lua_State* luaState;

    std::map<const char*, const char*> loadedScripts;

    void loadScript(const char* path) {
        std::string script = files::readFile(path);
        std::string name = files::extractFileName(path);
        loadedScripts.insert(std::pair<const char*, const char*>(name.c_str(), script.c_str()));
    }
}

void lua::init(const char* scriptsPath) {
    luaState = luaL_newstate();
    luaL_openlibs(luaState);

    // load all scripts
    // TODO: yap iste aq
}

void lua::bindAllSystems() {
    // bind timer Module
    getGlobalNamespace(luaState)
        .beginNamespace("timerModule")
            .addFunction("createTimer", timer::createTimer)
            .addFunction("resetTimer", timer::resetTimer)
            .addFunction("killTimer", timer::killTimer)
            .addFunction("getTimeDiff", timer::getTimeDiff)
            .addFunction("delay", timer::delay)
        .endNamespace();

    // bind engine Module
    getGlobalNamespace(luaState)
        .beginNamespace("engineModule")
            .addFunction("createContainer", engine::createContainer)
            .addFunction("deleteContainer", engine::deleteContainer)
            .addFunction("setLayer", engine::setLayer)
            .addFunction("closeAnimations", engine::closeAnimations)
            .addFunction("changeShaders", engine::changeShaders)
            .addFunction("getSpritePath", engine::getSpritePath)
            .addFunction("bindScriptToContainer", engine::bindScriptToContainer)
        .endNamespace();
}

void lua::bindAllClasses() {
    // bind Object class
    getGlobalNamespace(luaState)
        .beginClass<Object>("Object")
            .addFunction("show", &Object::show)
            .addFunction("hide", &Object::hide)
            .addFunction("isVisible", &Object::isVisible)
            .addFunction("getX", &Object::getX)
            .addFunction("getY", &Object::getY)
            .addFunction("getWidth", &Object::getWidth)
            .addFunction("getHeight", &Object::getHeight)
            .addFunction("getAngle", &Object::getAngle)
            .addFunction("getColor", &Object::getColor)
            .addFunction("setX", &Object::setX)
            .addFunction("setY", &Object::setY)
            .addFunction("setRotation", &Object::setRotation)
            .addFunction("setWidth", &Object::setWidth)
            .addFunction("setHeight", &Object::setHeight)
            .addFunction("setColor", &Object::setColor)
        .endClass();
}

void lua::runScript(const char* name) {
    // find a better and safer way to run scripts
    int scriptLoadStatus = luaL_dostring(luaState, loadedScripts[name]);

    if (scriptLoadStatus != 0)
        logError(lua_tostring(luaState, -1), scriptLoadStatus);
}

const char* lua::getScript(const char* name) {
    return loadedScripts[name];
}