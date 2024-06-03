//
// Created by Alan 01/06/2024
//

#include "EventDispatcher.h"

void EventDispatcher::DispatchMessage(sol::state& lua_state, Message& msg, NPC& receiver)
{
    // if no delay, send the message instantly
    if (msg.GetDelayTime() == 0) Send(lua_state, msg, receiver);
    // else store the message
    else m_MessageQue.insert(std::make_pair(msg, receiver));
    
}

void EventDispatcher::DispatchDelayedMessages(sol::state& lua_state, float deltaTime) 
{
    // if que is empty reset timer and return
    if (m_MessageQue.empty()) 
    {
        m_TimeElapsed = 0;
        return;
    } 
    else // else increment by deltaTime
    { 
        m_TimeElapsed += deltaTime;
    }

    // send all messages that the timer has elapsed, delete as we move to next message
    while (!m_MessageQue.empty() && m_MessageQue.begin()->first.GetDelayTime() <
           m_TimeElapsed) 
    {
        auto msg = m_MessageQue.begin()->first;
        auto& receiver = m_MessageQue.begin()->second;
        Send(lua_state, msg, receiver);
        m_MessageQue.erase(m_MessageQue.begin()); // erase current message after sending
    }
}

void EventDispatcher::Send(sol::state& lua_state, Message& msg, NPC& receiver) 
{
    receiver.GetFSM().HandleMessage(lua_state, msg);
}
