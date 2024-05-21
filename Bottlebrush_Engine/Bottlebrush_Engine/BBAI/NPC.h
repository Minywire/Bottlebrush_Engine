//
// Created by Alan 17/05/2024
//

#pragma once

#include <memory>

#include "FSM.h"
#include "BBScript.h"

class NPC 
{
public:
    NPC(const std::filesystem::path& statesPath, const std::string& initialState);

    virtual ~NPC();

    /// @author Alan
    /// @brief update call for FSM
    /// @param lua_state ai script to read from
    void Update(sol::state& lua_state);

    FSM<NPC>& GetFSM() { return m_FSM; }

private:
    FSM<NPC> m_FSM;

    /// @author Alan
    /// @brief init for FSM, setting up its lua path and states
    /// @param statesPath lua ai script
    /// @param initialState starting state to be in
    void initFSM(const std::filesystem::path& statesPath, const std::string& initialState);
};