//
// Created by Alan 01/06/2024
//

#include "Message.h"

Message::Message(std::string event, NPC* sender, float delayTime)
    : m_Sender(sender), m_Event(event), m_DelayTime(delayTime) 
{

}

NPC& Message::GetSender() 
{ 
	return *m_Sender; 
}

std::string& Message::GetEvent()
{
	return m_Event;
}

const float Message::GetDelayTime() const
{
	return m_DelayTime;
}


bool Message::operator<(const Message& otherMsg) const
{ 
	return m_DelayTime < otherMsg.m_DelayTime;
}
