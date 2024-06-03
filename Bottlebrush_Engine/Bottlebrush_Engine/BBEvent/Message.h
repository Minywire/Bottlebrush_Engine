//
// Created by Alan 01/06/2024
//

#pragma once

#include <string>

class NPC;

/// @author Alan
/// @brief Struct used to relaying an event to all listeners
class Message
{
public:
    Message(std::string event, NPC* sender);

    NPC* GetSender();
    Event GetEvent();
private:
    std::string m_Event;
    NPC* m_Sender;
};
