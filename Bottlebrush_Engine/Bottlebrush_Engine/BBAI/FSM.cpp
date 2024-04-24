//
// Created by Alan 24/04/2024
//

#include "FSM.h"

FSM::FSM() 
	: m_currentState(FSMState::IDLE) 
{

}

void FSM::HandleEvent(FSMEvent event)
{
	switch (event)
	{
		case FSMEvent::PlayerSpotted:
            m_currentState = FSMState::CHASE;
			break;
		case FSMEvent::PlayerLost:
			m_currentState = FSMState::IDLE;
			break;
		case FSMEvent::PatrolMode:
			m_currentState = FSMState::PATROL;
			break;
	}
}

FSMState FSM::GetCurrentState() const { return m_currentState; }
