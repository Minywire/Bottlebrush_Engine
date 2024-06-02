//
// Created by Alan 01/06/2024
//

#pragma once

#include <string>

class NPC;

/// @author Alan
/// @brief Struct used to relaying an event to all listeners
struct Message
{
public:
    Message(std::string event, NPC* sender)
        : m_Sender(sender), m_Event(event) {}

    NPC* GetSender() { return m_Sender; }
private:
    std::string m_Event;
    NPC* m_Sender;
};
