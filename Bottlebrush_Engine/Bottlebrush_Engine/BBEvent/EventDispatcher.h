//
// Created by Alan 01/06/2024
//

#pragma once

#include "Message.h"
#include "sol/sol.hpp"
#include "NPC.h"

/// @author Alan
/// @brief Handles and dispatches events
class EventDispatcher 
{
public:
    void DispatchMessage(sol::state& lua_state, Message& msg, NPC& receiver);

private:
    void Send(sol::state& lua_state, Message& msg, NPC& receiver);
};
