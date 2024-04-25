//
// Created by Alan 24/04/2024
//

#include "NPC.h"

#include <iostream>

NPC::NPC(FSM fsm) 
    :   m_fsm(fsm)
{

}

void NPC::Update()
{

    // currently outputing current state to terminal
    switch (m_fsm.GetCurrentState())
    {
        case FSMState::IDLE:
            std::cout << "NPC is idling" << std::endl;
            break;
        case FSMState::PATROL:
            std::cout << "NPC is patrolling" << std::endl;
            break;
        case FSMState::SEEK:
            std::cout << "NPC is seeking" << std::endl;
            break;
        case FSMState::CHASE:
            std::cout << "NPC is chasing" << std::endl;
            break;
    }
}

void NPC::SpotPlayer()
{
    m_fsm.HandleEvent(FSMEvent::PlayerSpotted);
}

void NPC::LosePlayer()
{
    m_fsm.HandleEvent(FSMEvent::PlayerLost);
}
