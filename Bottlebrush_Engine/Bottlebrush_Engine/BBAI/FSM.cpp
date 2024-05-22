//
// Created by Alan 24/04/2024
//

#include "FSM.h"
#include "NPC.h"

FSM::FSM(NPC* FSMOwner, const std::filesystem::path& statesPath, const std::string& initialState) : 
    m_fsmOwner(FSMOwner),
    m_currentState(initialState),
    m_globalState("Global"),
    m_previousState(initialState) 
{
    SetStatePath(statesPath);
    std::cout << "State Path: " << statesPath.string() << std::endl;  //@Debug Line, to be removed
    std::cout << "Initial State: " << initialState << std::endl;  //@Debug Line, to be removed
}

void FSM::update(sol::state & lua_state)
{
    if (m_globalState.compare("") != 0 && lua_state[m_globalState].valid())
    {
        lua_state[m_globalState]["Update"](*m_fsmOwner);
    } 
    else
    {
        throw std::runtime_error("AI Global not found");
    }

    if (m_currentState.compare("") != 0 && lua_state[m_currentState].valid())
    {
        lua_state[m_currentState]["Update"](*m_fsmOwner);
    }
    else
    {
        std::string errMsg = "AI state: " + m_currentState + " not found";
        throw std::runtime_error(errMsg);
    }
}

void FSM::SetStatePath(const std::filesystem::path& path)
{
	if(path.extension() != ".lua") { throw std::runtime_error("Lua file is no lua file"); }
	m_statePath = path;
}

std::filesystem::path& FSM::GetStatePath() 
{ 
    return m_statePath; 
}
