//
// Created by Alan 01/06/2024
//

#include "EventDispatcher.h"

EventDispatcher::EventDispatcher() 
{

}

void EventDispatcher::DispatchMessage(sol::state& lua_state,const Message& msg, NPC* sender, NPC* reciever)
{
    Send(lua_state, msg, reciever);
}

void EventDispatcher::Send(sol::state& lua_state, const Message& msg, NPC* receiver) 
{
    receiver->GetFSM().HandleMessage(lua_state, msg);
    std::cout << "EventDispatcher: Message Sent" << std::endl;
}
