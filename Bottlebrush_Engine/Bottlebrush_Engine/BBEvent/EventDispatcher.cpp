//
// Created by Alan 01/06/2024
//

#include "EventDispatcher.h"

EventDispatcher::EventDispatcher() 
{

}

void EventDispatcher::DispatchMessage(const Message& msg, NPC* sender, NPC* reciever)
{
    Send(msg, reciever);
}

void EventDispatcher::Send(const Message& msg, NPC* receiver) 
{
    std::cout << "Message Sent" << std::endl;
}
