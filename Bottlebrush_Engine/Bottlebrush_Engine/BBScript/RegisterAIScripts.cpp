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

void registerScriptedNPC(sol::state& lua_state, ECS& ecs) {
    lua_state.new_usertype<NPC>("NPC", 
        "AddWaypoint", &NPC::AddWaypoint
    );

    auto movementTable = lua_state["Movement"].get_or_create<sol::table>();
    movementTable["Patrol"] = [&ecs](NPC& npc) { npc.Patrol(ecs); };
    movementTable["MoveTo"] = [&ecs](NPC& npc, const glm::vec2& vec2) { npc.MoveTo(vec2, ecs); };
}

void registerScriptedGLM(sol::state& lua_state) {
    lua_state.new_usertype<glm::vec2>("vec2",
        sol::call_constructor,
        sol::constructors<glm::vec2(), glm::vec2(float, float)>()
    );
}

} // namespace AIScripts
