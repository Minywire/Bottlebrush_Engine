//
// Created by Alan 17/05/2024
//

#pragma once

#include "BBScript.h"
#include "FSM.h"

/// @author Alan
/// @brief NPC class that holds an FSM to determine it's states and transitions
/// This class will incorporate game functions such as movement and sensory methods
class NPC 
{
public:
    NPC(const std::filesystem::path& statesPath, const std::string& initialState);

    /// @author Alan
    /// @brief update call for FSM
    /// @param lua_state ai script to read from
    void Update(sol::state& lua_state);

    FSM& GetFSM();

private:
    FSM m_FSM;
};