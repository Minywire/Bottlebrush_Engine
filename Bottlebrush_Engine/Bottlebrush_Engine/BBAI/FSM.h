//
// Created by Alan 24/04/2024
//

#pragma once

#include <string>
#include <filesystem>
#include <sol/sol.hpp>

class NPC;

/// @author Alan
/// @brief Finite State Machine for NPCs, handles updating within game loop with AI Scripts
/// and changing states
class FSM
{
public:
    FSM(NPC* FSMOwner, const std::filesystem::path& statesPath,
        const std::string& initialState, sol::state& lua_state);

    /// @author Alan
    /// @brief normal update call for state machine
    /// runs current state update, and global state update
    void update();

    /// @author Alan
    /// @brief changes states, updates previous state, runs onExit and onEnter
    /// accordingly
    /// @param newState the new state to transition to
    void changeState(const std::string& newState);

    /// @author Alan
    /// @brief evaluate if path extension is correct and then sets the member statePath its value
    /// @param path the string to get the ai script
    void setStatePath(const std::filesystem::path& path);

    std::filesystem::path& getStatePath();

private:
    NPC* m_npcReference; // reference to the NPC that owns this FSM

    std::filesystem::path m_statePath; // relative file path to the AI scripts

    std::string m_previousState;
    std::string m_globalState;
    std::string m_currentState;

    sol::state& m_luaState;
};
