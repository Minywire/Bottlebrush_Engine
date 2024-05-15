//
// Created by Alan 24/04/2024
//

#include "FSM.h"

template <typename entity_type>
FSM<entity_type>::FSM(entity_type* FSMowner) : 
	m_owner(FSMowner), 
	m_currentState(NULL), 
	m_globalState(NULL), 
	m_previousState(NULL) 
{

}

template <typename entity_type>
FSM<entity_type>::~FSM() 
{

}

template <typename entity_type>
void FSM<entity_type>::update() const 
{
	if (m_globalState) m_globalState->Update(m_owner);
	
	if (m_currentState) m_currentState->Update(m_owner);
}

template <typename entity_type>
void FSM<entity_type>::changeState(State<entity_type>* newState) 
{
	m_previousState = m_currentState;	// track previous state
	m_currentState->onExit(m_owner);	// execute exit code
	m_currentState = newState;			// change states
	m_currentState->onEnter(m_owner);	// execute enter code of new state
}

template <typename entity_type>
void FSM<entity_type>::revertToPreviousState() 
{
	m_currentState = m_previousState;
}

template <typename entity_type>
bool FSM<entity_type>::isInState(const State<entity_type>& st) const 
{
        return typeid(*m_currentState) == typeid(st);
}

template <typename entity_type>
void FSM<entity_type>::setPreviousState(const State<entity_type>* st) 
{
	m_previousState = st;
}

template <typename entity_type>
void FSM<entity_type>::setCurrentState(const State<entity_type>* st) 
{
	m_currentState = st;
}

template <typename entity_type>
void FSM<entity_type>::setGlobalState(const State<entity_type>* st) 
{
	m_globalState = st;
}

template <typename entity_type>
State<entity_type>& FSM<entity_type>::getPreviousState() 
{
	return m_previousState;
}

template <typename entity_type>
State<entity_type>& FSM<entity_type>::getCurrentState() 
{
	return m_currentState;
}

template <typename entity_type>
State<entity_type>& FSM<entity_type>::getGlobalState() 
{
	return m_globalState;
}
