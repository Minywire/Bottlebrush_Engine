//
// Created by Alan 01/06/2024
//

#pragma once

#include <map>

#include "Message.h"
#include "sol/sol.hpp"
#include "NPC.h"

/// @author Alan
/// @brief Handles and dispatches events
class EventDispatcher 
{
public:
    void DispatchMessage(sol::state& lua_state, Message& msg, NPC& receiver);
    void DispatchDelayedMessages(sol::state& lua_state, float deltaTime);
private:
    float m_TimeElapsed = 0; // used to check if delayed messages are past the timer.
    std::multimap<Message, NPC> m_MessageQue; // que for delayed messages
    void Send(sol::state& lua_state, Message& msg, NPC& receiver);
};
