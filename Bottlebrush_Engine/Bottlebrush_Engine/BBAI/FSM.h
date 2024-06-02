//
// Created by Alan 24/04/2024
//

#pragma once

#include <string>
#include <filesystem>
#include <sol/sol.hpp>

/** forward decl to avoid circle linking */
class Message;
class NPC;

/// @author Alan
/// @brief Finite State Machine for NPCs, handles updating within game loop with AI Scripts
/// and changing states
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
    /// @brief changes states, updates previous state, runs onExit and onEnter
    /// accordingly
    /// @param newState the new state to transition to
    /// @param lua_state used to reference to the next section of the script to run
    void ChangeState(const std::string& newState, sol::state& lua_state);

    /// @author Alan
    /// @brief evaluate if path extension is correct and then sets the member statePath its value
    /// @param path the string to get the ai script
    void SetStatePath(const std::filesystem::path& path);

    std::filesystem::path& GetStatePath();

    /// @author Alan
    /// @brief sends message to appropriate state's "onMessage" function if there is one
    /// @param lua_state used to reference to the next section of the script to run
    /// @param msg event message
    /// @return if message is handled or not
    bool HandleMessage(sol::state& lua_state, Message& msg);

private:
    NPC* m_npcReference; // reference to the NPC that owns this FSM

    std::filesystem::path m_statePath; // relative file path to the AI scripts

    std::string m_previousState;
    std::string m_globalState;
    std::string m_currentState;
};
