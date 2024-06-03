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
    Message(std::string event, NPC* sender, float delayTime);

    std::string& GetEvent();
    NPC& GetSender();
    const float GetDelayTime() const;

    /// @author Alan
    /// @brief used to sort in order in Event Dispatcher if message is delayed
    /// @return if this message takes less time than another message
    bool operator<(const Message& otherMsg) const;
private:
    std::string m_Event; // event to send
    NPC* m_Sender; // the sending NPC
    const float m_DelayTime; // adding delay time to sending the message
};
