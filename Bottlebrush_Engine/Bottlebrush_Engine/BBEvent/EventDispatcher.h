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
    void DispatchMessage(sol::state& lua_state, Message& msg, NPC* sender, NPC* reciever);

private:
    void Send(sol::state& lua_state, Message& msg, NPC* receiver);
};
