#pragma once

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

using namespace luabridge;

namespace lua {
    /**
     * @brief Creates a new Lua state and loads static scripts.
     * 
     * This function should be called before any other Lua functions.
     * 
     * @param staticScriptsPath The path to the directory containing static scripts.
     */
    void init(const char* staticScriptsPath = "./data/scripts/static/");

    void bindAllSystems();
    void bindAllClasses();

    /**
     * @brief Runs a loaded Lua script.
     * 
     * @param name The name of the script to run.
     */
    void runScript(const char* name);

    const char* getScript(const char* name);
}
