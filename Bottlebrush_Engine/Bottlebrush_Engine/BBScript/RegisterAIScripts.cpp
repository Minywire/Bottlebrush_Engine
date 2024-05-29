//
// Created by Alan 27/05/2024
//

#include "RegisterAIScripts.h"
#include "FSM.h"
#include "NPC.h"

namespace AIScripts {

void registerScriptedFSM(sol::state& lua_state) {
    auto fsmTable = lua_state["FSM"].get_or_create<sol::table>();
    fsmTable["ChangeState"] = [&lua_state](NPC& npc, const std::string& state)
    {
        npc.GetFSM().ChangeState(state, lua_state);
    };
}

void registerScriptedNPC(sol::state& lua_state) {
    lua_state.new_usertype<NPC>("NPC", 
        "MoveTo", &NPC::MoveTo,
        "AddWaypoint", &NPC::AddWaypoint,
        "Patrol", &NPC::Patrol
    );
}

void registerScriptedGLM(sol::state& lua_state) {
    lua_state.new_usertype<glm::vec2>("vec2",
        sol::call_constructor,
        sol::constructors<glm::vec2(), glm::vec2(float, float)>()
    );
}

} // namespace AIScripts
