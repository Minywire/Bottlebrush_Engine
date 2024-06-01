//
// Created by Alan 01/06/2024
//

#pragma once

#include "NPC.h"

enum class Event 
{ 
	PLAYERSPOTTED
};

/// @author Alan
/// @brief Class used to relaying an event to all listeners
class Message
{
public:
    Message();
private:
    Event m_Event;
    NPC* m_Sender;
    NPC* m_Receiver;
    float m_DispatchTime;
};
