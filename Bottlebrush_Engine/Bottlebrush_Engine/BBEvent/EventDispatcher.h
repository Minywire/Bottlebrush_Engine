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

    void DispatchMessage(const Message& msg, NPC* sender, NPC* reciever);

private:
    std::set<Message> m_MessageQue;

    void Send(const Message& msg, NPC* receiver);
};
