//
// Created by Alan 27/05/2024
//

#pragma once

#include "BBScript.h"
#include "ECS.h"

/** forward declaration to avoid circle linking */
//class ECS;

namespace AIScripts {

void registerScriptedFSM(sol::state& lua_state);

void registerScriptedNPC(sol::state& lua_state, ECS& ecs);
void registerScriptedGLM(sol::state& lua_state);


}
