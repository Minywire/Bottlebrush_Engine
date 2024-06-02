//
// Created by Alan 01/06/2024
//

#pragma once

#include <set>

#include "Message.h"

/// @author Alan
/// @brief Handles and dispatches events
class EventDispatcher 
{
public:
    EventDispatcher();

    void DispatchMessage(sol::state& lua_state, Message& msg, NPC* sender, NPC* reciever);

private:
    std::set<Message> m_MessageQue;

    void Send(sol::state& lua_state, Message& msg, NPC* receiver);
};
