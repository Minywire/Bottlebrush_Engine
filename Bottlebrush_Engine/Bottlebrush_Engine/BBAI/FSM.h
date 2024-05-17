//
// Created by Alan 24/04/2024
//

#include "State.h"

/// @author Alan
/// @brief Finite State Machine for NPCs
template <typename entity_type>
class FSM
{
public:
	FSM(entity_type* FSMowner) : 
		m_owner(FSMowner), 
		m_currentState(NULL), 
		m_globalState(NULL), 
		m_previousState(NULL) 
	{};

	virtual ~FSM() {};

	/// @author Alan
	/// @brief normal update call for state machine
	/// runs current state update, and global state update
	void update() const
	{
		if (m_globalState) m_globalState->Update(m_owner);
	
		if (m_currentState) m_currentState->Update(m_owner);
	}

	/// @author Alan
	/// @brief changes states, updates previous state, runs onExit and onEnter accordingly
	/// @param newState the new state to transition to
	void changeState(State<entity_type>* newState) {
        m_previousState = m_currentState;  // track previous state
        m_currentState->onExit(m_owner);   // execute exit code
        m_currentState = newState;         // change states
        m_currentState->onEnter(m_owner);  // execute enter code of new state
    }  // @TODO find lua object to replace State<entity_type>

	/// @author Alan
	/// @brief reverts back to original state, used with globalState changing states temporarily
    void revertToPreviousState() { m_currentState = m_previousState; }

	/// @author Alan
	/// @brief checks whether the param st is indeed what the current state is
	/// @param st is the state to check whether the FSM is currently in
	/// @return true or false of whether it is currently in that state or not
	bool isInState(const State<entity_type>& st) const { return typeid(*m_currentState) == typeid(st); } // @TODO find lua object to replace State<entity_type>

	// set states
	void setPreviousState(const State<entity_type>* st) { m_previousState = st; } // @TODO find lua object to replace State<entity_type>
	void setCurrentState(const State<entity_type>* st) { m_currentState = st; }
	void setGlobalState(const State<entity_type>* st) { m_globalState = st; }

	State<entity_type>& getPreviousState() { return m_previousState; } // @TODO find lua object to replace State<entity_type>
	State<entity_type>& getCurrentState() { return m_currentState; }
	State<entity_type>& getGlobalState() { return m_globalState; }

private:
	entity_type* m_owner; // owning AI object
	
	State<entity_type>* m_previousState; // @TODO find lua object to replace State<entity_type>
	State<entity_type>* m_globalState;
	State<entity_type>* m_currentState;
};
