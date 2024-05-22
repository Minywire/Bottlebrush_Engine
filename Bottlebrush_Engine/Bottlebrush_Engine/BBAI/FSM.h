//
// Created by Alan 24/04/2024
//

#pragma once

#include <string>
#include <filesystem>

#include "BBScript.h"

class NPC;

/// @author Alan
/// @brief Finite State Machine for NPCs
class FSM
{
public:
	FSM(NPC* FSMOwner, const std::filesystem::path& statesPath, const std::string& initialState);

	/// @author Alan
	/// @brief normal update call for state machine
	/// runs current state update, and global state update
	/// @param lua_state the script to read from
	void update(sol::state & lua_state);

	/// @author Alan
	/// @brief changes states, updates previous state, runs onExit and onEnter accordingly
	/// @param newState the new state to transition to
	/// @param lua_state the script to read from
	void changeState(const std::string& newState, sol::state & lua_state);

	/// @author Alan
	/// @brief reverts back to original state, used with globalState changing states temporarily
	void revertToPreviousState() { m_currentState = m_previousState; }

	/// @author Alan
	/// @brief checks whether the param st is indeed what the current state is
	/// @param st is the state to check whether the FSM is currently in
	/// @return true or false of whether it is currently in that state or not
	bool isInState(const std::string& st) const { return m_currentState.compare(st) == 0; }

	// set states
	void SetPreviousState(const std::string& st) { m_previousState = st; } 
	void SetCurrentState(const std::string& st) { m_currentState = st; }
	void SetGlobalState(const std::string& st) { m_globalState = st; }

	std::string& GetPreviousState() { return m_previousState; }
	std::string& GetCurrentState() { return m_currentState; }
	std::string& GetGlobalState() { return m_globalState; }

	void SetStatePath(const std::filesystem::path& path);

	std::filesystem::path GetStatePath() { return m_statePath; }

private:
	NPC* m_fsmOwner; // owning AI object

	std::filesystem::path m_statePath;

	std::string m_previousState;
	std::string m_globalState;
	std::string m_currentState;
};
