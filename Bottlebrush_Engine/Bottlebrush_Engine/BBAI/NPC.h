//
// Created by Alan 17/05/2024
//

#pragma once

#include "BBScript.h"
#include "FSM.h"

class NPC 
{
public:
    NPC(const std::filesystem::path& statesPath, const std::string& initialState);

    virtual ~NPC();

    /// @author Alan
    /// @brief update call for FSM
    /// @param lua_state ai script to read from
    void Update(sol::state& lua_state);

    FSM& GetFSM() { return m_FSM; }

private:
    FSM m_FSM;
};