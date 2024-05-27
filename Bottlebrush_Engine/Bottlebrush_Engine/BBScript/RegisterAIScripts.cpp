//
// Created by Alan 27/05/2024
//

#include "RegisterAIScripts.h"
#include "FSM.h"
#include "NPC.h"


void registerScriptedFSM(sol::state& lua_state) {
    lua_state.new_usertype<FSM>("FSM", 
        sol::constructors<FSM(NPC*, const std::filesystem::path&, const std::string&, sol::state&)>(),
        "changeState", &FSM::changeState
    );
}

void registerScriptedNPC(sol::state& lua_state) {
    lua_state.new_usertype<NPC>("NPC", 
        sol::constructors<NPC(const std::filesystem::path&, const std::string&, sol::state&)>(),
        "getFSM", &NPC::getFSM
    );
}
