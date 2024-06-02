//
// Created by Alan 27/05/2024
//

#include "RegisterAIScripts.h"
#include "FSM.h"
#include "NPC.h"
#include "Message.h"

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
        "GetPosition", &NPC::GetVec2Position,
        "GetLastPlayerLocation", &NPC::GetLastPlayerLoc,
        "IsMoving", &NPC::IsMoving
    );

    // register movement functions that depend on transform component
    auto movementTable = lua_state["Movement"].get_or_create<sol::table>();
    movementTable["Patrol"] = [&ecs](NPC& npc) { npc.Patrol(ecs); };
    movementTable["MoveTo"] = [&ecs](NPC& npc, glm::vec2& vec2) { npc.MoveTo(vec2, ecs); };
    movementTable["ChasePlayer"] = [&ecs, &player](NPC& npc) 
    { 
        glm::vec2 pos = {player.GetPositionX(), player.GetPositionZ()};
        npc.SetLastPlayerLoc(pos);
        npc.MoveTo(pos, ecs); 
        return npc.IsMoving();
    };

    // register detection functions that depend on transform component
    auto detectionTable = lua_state["Detection"].get_or_create<sol::table>();
    detectionTable["SeePlayer"] = [&player, &ecs](NPC& npc) { return npc.SeePlayer(glm::vec2(player.GetPositionX(), player.GetPositionZ()), ecs); };
    detectionTable["InMessageRange"] = [&ecs](NPC& npc, Message& msg, float range)
    {
        glm::vec2 curPos = npc.GetVec2Position(ecs);
        glm::vec2 theirPos = msg.GetSender()->GetVec2Position(ecs);
        float distance = glm::length(theirPos - curPos);
        return distance < range;
    };

    // register EventDispatcher table functions that depend on lua_state
    auto dispatchTable = lua_state["Dispatch"].get_or_create<sol::table>();
    dispatchTable["SendMessage"] = [&ecs, &lua_state](Message& msg)
    {
        if (!msg.GetSender()->SendMessage(ecs, lua_state, msg))
        {
            std::cout << "Failed to send message" << std::endl;
        }
    };
}

void registerScriptedGLM(sol::state& lua_state) {
    lua_state.new_usertype<glm::vec2>("vec2",
        sol::call_constructor,
        sol::constructors<glm::vec2(), glm::vec2(float, float)>()
    );
}

void registerScriptedMessage(sol::state& lua_state) {
    // register Event enum
    lua_state.new_enum("Event",
        "PlayerSpotted", Event::PLAYERSPOTTED
    );

    // register Message system
    lua_state.new_usertype<Message>("Message",
        sol::call_constructor,
        sol::constructors<Message(Event, NPC*)>(),
        "GetEvent", &Message::GetEvent,
        "GetSender", &Message::GetSender
    );
}

}  // namespace AIScripts
