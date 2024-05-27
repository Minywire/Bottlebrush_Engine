//
// Created by Alan 27/05/2024
//

#include "RegisterAIScripts.h"
#include "FSM.h"
#include "NPC.h"

void registerScriptedFSM(sol::state& lua_state) {
  lua_state.new_usertype<FSM>("FSM", 
      "changeState", &FSM::changeState
  );
}