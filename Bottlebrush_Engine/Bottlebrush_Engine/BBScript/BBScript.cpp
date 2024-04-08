//
// Created by Marco Garzon Lara and Niamh Wilson on 21/3/2024.
//

#include "BBScript.h"

BBScript::BBScript() { luaState.open_libraries(sol::lib::base); }

sol::state & BBScript::getLuaState()
{
    return luaState;
}