//
// Created by Marco Garzon Lara and Niamh Wilson on 21/3/2024.
//
#pragma once

#include <lua-5.4.6/lua.hpp>
#include <sol/sol.hpp>

/**
 * @class BBScript
 *
 * @brief The Lua manager class
 */
class BBScript
{
public:
    BBScript();

    /*
    * @return The encapsulated lua state for modification.
    */
    sol::state& getLuaState();
private:
    sol::state luaState; ///The lua state for the script system

};
