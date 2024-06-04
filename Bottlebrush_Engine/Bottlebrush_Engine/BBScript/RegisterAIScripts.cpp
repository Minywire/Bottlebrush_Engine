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
    // register player functions
    lua_state.new_usertype<NPC>("NPC", 
        "AddWaypoint", &NPC::AddWaypoint,
        "StopMoving", &NPC::StopMoving,
        "SetWaitDuration", &NPC::SetWaitDuration,
        "IsWaiting", &NPC::IsWaiting,
        "ClearWaitDuration", &NPC::ClearWaitDuration,
        "ClearWaitTimeElapsed", &NPC::ClearWaitTimeElapsed,
        "ClearAllTimers", &NPC::ClearAllTimers,
        "GetLastMoveTo", &NPC::GetLastMoveTo,
        "IsMoving", &NPC::IsMoving,
        "SetWander", &NPC::SetWander
    );

    // register movement functions that depend on transform component
    auto movementTable = lua_state["Movement"].get_or_create<sol::table>();
    movementTable["Patrol"] = [&ecs](NPC& npc) { npc.Patrol(ecs); };
    movementTable["MoveTo"] = [&ecs](NPC& npc, const glm::vec2& vec2) { npc.MoveTo(vec2, ecs); };
    movementTable["ChasePlayer"] = [&ecs, &player](NPC& npc) 
    { 
        glm::vec2 pos = {player.GetPositionX(), player.GetPositionZ()};
        npc.MoveTo(pos, ecs);
        return npc.IsMoving();
    };
    movementTable["Wander"] = [&ecs](NPC& npc) { npc.Wander(ecs); };

    // register detection functions that depend on transform component
    auto detectionTable = lua_state["Detection"].get_or_create<sol::table>();
    detectionTable["SeePlayer"] = [&player, &ecs](NPC& npc) { return npc.SeePlayer(glm::vec2(player.GetPositionX(), player.GetPositionZ()), ecs); };

    // register EventDispatcher table functions that depend on lua_state
    auto dispatchTable = lua_state["Dispatch"].get_or_create<sol::table>();
    dispatchTable["SendMessage"] = [&ecs, &lua_state](std::string event, NPC& npc, float delayTime = 0) 
    {
        auto msg = Message{
            .m_Event = event,
            .m_Sender = &npc,
            .m_DelayTime = delayTime,
        };

        npc.SendMessage(ecs, lua_state, msg);
    };
    dispatchTable["InMessageRange"] = [&ecs](NPC& npc, Message& msg, float range) 
    {
        glm::vec2 curPos = npc.GetVec2Position(ecs);
        glm::vec2 theirPos = msg.m_Sender->GetVec2Position(ecs);
        float distance = glm::length(theirPos - curPos);
        return distance < range;
    };
    dispatchTable["GetVec2SenderLocation"] = [&ecs](Message& msg)
    {
        return msg.m_Sender->GetVec2Position(ecs);
    };
}

void registerScriptedGLM(sol::state& lua_state) {
    lua_state.new_usertype<glm::vec2>("vec2",
        sol::call_constructor,
        sol::constructors<glm::vec2(), glm::vec2(float, float)>()
    );
}

void registerScriptedAnimation(sol::state& lua_state, ECS& ecs) {
    auto animationTable = lua_state["Animation"].get_or_create<sol::table>();
    animationTable["SetAnimation"] = [&ecs](NPC& npc, std::string animName) 
    {
        auto& md2Comp = npc.GetEntity().GetComponent<MD2Component>(ecs.getReg());

        md2Comp.current_animation = animName;
    };
}
void registerScriptedMessage(sol::state& lua_state) {
    // register Message system
    lua_state.new_usertype<Message>("Message",
        "Event", &Message::m_Event
    );
}

}  // namespace AIScripts
