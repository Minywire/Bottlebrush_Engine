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

void registerScriptedNPC(sol::state& lua_state, ECS& ecs, const Camera& player) {
    lua_state.new_usertype<NPC>("NPC", 
        "AddWaypoint", &NPC::AddWaypoint,
        "StopMoving", &NPC::StopMoving,
        "SetWaitDuration", &NPC::SetWaitDuration,
        "IsWaiting", &NPC::IsWaiting
    );

    auto movementTable = lua_state["Movement"].get_or_create<sol::table>();
    movementTable["Patrol"] = [&ecs](NPC& npc) { npc.Patrol(ecs); };
    movementTable["MoveTo"] = [&ecs](NPC& npc, const glm::vec2& vec2) { npc.MoveTo(vec2, ecs); };
    movementTable["ChasePlayer"] = [&ecs, &player](NPC& npc) 
    { 
        glm::vec2 pos = {player.GetPositionX(), player.GetPositionZ()};
        npc.MoveTo(pos, ecs); 
    };

    auto detectionTable = lua_state["Detection"].get_or_create<sol::table>();
    detectionTable["SeePlayer"] = [&player, &ecs](NPC& npc) { return npc.SeePlayer(glm::vec2(player.GetPositionX(), player.GetPositionZ()), ecs); };
}

void registerScriptedGLM(sol::state& lua_state) {
    lua_state.new_usertype<glm::vec2>("vec2",
        sol::call_constructor,
        sol::constructors<glm::vec2(), glm::vec2(float, float)>()
    );
}

} // namespace AIScripts
