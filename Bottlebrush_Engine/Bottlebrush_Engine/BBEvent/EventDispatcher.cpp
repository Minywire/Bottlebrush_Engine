//
// Created by Alan 01/06/2024
//

#include "EventDispatcher.h"

void EventDispatcher::DispatchMessage(sol::state& lua_state, Message& msg, NPC* sender, NPC* receiver)
{
    if (!receiver) 
    {
        std::cout << "Receiver NPC is invalid" << std::endl;
        return;
    }
    Send(lua_state, msg, receiver);
}

void EventDispatcher::Send(sol::state& lua_state, Message& msg, NPC* receiver) 
{
    if(receiver->GetFSM().HandleMessage(lua_state, msg))
        std::cout << "EventDispatcher: Message Sent" << std::endl;
    else
        std::cout << "EventDispatcher: Message Failed to send" << std::endl;
}
