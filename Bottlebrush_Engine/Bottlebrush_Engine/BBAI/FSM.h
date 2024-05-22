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

	void SetStatePath(const std::filesystem::path& path);

	std::filesystem::path& GetStatePath() { return m_statePath; }

private:
	NPC* m_fsmOwner; // owning AI object

	std::filesystem::path m_statePath;

	std::string m_previousState;
	std::string m_globalState;
	std::string m_currentState;
};
