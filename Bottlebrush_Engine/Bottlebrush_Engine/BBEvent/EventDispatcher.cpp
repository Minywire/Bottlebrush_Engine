//
// Created by Alan 01/06/2024
//

#include "EventDispatcher.h"

void EventDispatcher::DispatchMessage(sol::state& lua_state, Message& msg, NPC& receiver)
{
    Send(lua_state, msg, receiver);
}

void EventDispatcher::Send(sol::state& lua_state, Message& msg, NPC& receiver) 
{
    receiver.GetFSM().HandleMessage(lua_state, msg);
}
