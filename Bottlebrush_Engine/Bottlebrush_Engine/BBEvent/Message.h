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
    std::string m_Event;
    NPC* m_Sender;
    const float m_DelayTime; // adding delay time to sending the message
};
