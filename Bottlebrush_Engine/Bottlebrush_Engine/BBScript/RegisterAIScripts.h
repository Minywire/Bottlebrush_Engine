//
// Created by Alan 27/05/2024
//

#pragma once

#include "BBScript.h"

namespace AIScripts {

void registerScriptedFSM(sol::state& lua_state);
void registerScriptedNPC(sol::state& lua_state);
void registerScriptedGLM(sol::state& lua_state);

}
