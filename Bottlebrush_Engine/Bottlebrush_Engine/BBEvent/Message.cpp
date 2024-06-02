//
// Created by Alan 01/06/2024
//

#include "Message.h"

Message::Message(Event event, NPC& sender) :
	m_Sender(sender),
	m_Event(event)
{
	
}

NPC& Message::GetSender()
{
	return m_Sender;
}
