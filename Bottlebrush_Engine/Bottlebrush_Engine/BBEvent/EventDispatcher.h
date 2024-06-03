//
// Created by Alan 01/06/2024
//

#pragma once

#include <map>

#include "Message.h"
#include "sol/sol.hpp"
#include "NPC.h"

struct messageCompareFunc
{
    bool operator()(const Message& thisMsg, const Message& otherMsg) const {
        return thisMsg.m_DelayTime < otherMsg.m_DelayTime;
    };
};

/// @author Alan
/// @brief Handles and dispatches events
class EventDispatcher 
{
public:
    /// @author Alan
    /// @brief sends a message instantly if no delay is on it, else stores the message to be sent later
    /// @param lua_state to pass to the FSM to read sol_state
    /// @param msg the Message with an event string and sender reference
    /// @param receiver the NPC that will receive the message
    void DispatchMessage(sol::state& lua_state, Message& msg, NPC& receiver);

    /// @author Alan
    /// @brief dispatches any delayed messages if enough time has elapsed
    /// @param lua_state to pass to the FSM to read sol_state 
    /// @param deltaTime to increment m_TimeElapsed
    void DispatchDelayedMessages(sol::state& lua_state, float deltaTime);
private:
    float m_TimeElapsed = 0; // used to check if delayed messages are past the timer.
    std::multimap<Message, NPC, messageCompareFunc> m_MessageQue; // que for delayed messages

    /// @author Alan
    /// @brief sends a message to the receiver
    /// @param lua_state to pass to the FSM to read sol_state 
    /// @param msg the Message with an event string and sender reference 
    /// @param receiver the NPC that will receive the message
    void Send(sol::state& lua_state, Message& msg, NPC& receiver);
};