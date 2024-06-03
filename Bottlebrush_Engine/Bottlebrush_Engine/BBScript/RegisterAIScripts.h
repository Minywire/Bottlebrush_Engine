//
// Created by Alan 27/05/2024
//

#pragma once

#include "BBScript.h"
#include "ECS.h"
#include "Camera.h"
#include "Message.h"
#include "BBMD2.h"

namespace AIScripts {

void registerScriptedFSM(sol::state& lua_state);
void registerScriptedNPC(sol::state& lua_state, ECS& ecs, const Camera& player);
void registerScriptedGLM(sol::state& lua_state);
void registerScriptedAnimation(sol::state& lua_state, ECS& ecs, std::unordered_map<std::string, BBMD2>& sceneMD2Models);

}
