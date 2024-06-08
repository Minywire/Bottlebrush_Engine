//
// Created by Alan 24/04/2024
//

#include "FSM.h"
#include "NPC.h"

FSM::FSM(NPC* FSMOwner, const std::filesystem::path& statesPath,
         const std::string& initialState, const std::string& globalState)
    : 
    m_npcReference(FSMOwner),
    m_statePath(statesPath),
    m_previousState(initialState),
    m_globalState(globalState),
    m_currentState(initialState)
{

}

void FSM::update(sol::state & lua_state)
{
    if (m_globalState.compare("") != 0 && lua_state[m_globalState].valid())
    {
        lua_state[m_globalState]["Update"](*m_npcReference);
    } 
    else
    {
        throw std::runtime_error("AI Global not found");
    }

    if (m_currentState.compare("") != 0 && lua_state[m_currentState].valid())
    {
        lua_state[m_currentState]["Update"](*m_npcReference);
    }
    else
    {
        std::string errMsg = "AI state: " + m_currentState + " not found";
        throw std::runtime_error(errMsg);
    }
}

void FSM::ChangeState(const std::string& newState, sol::state& lua_state) 
{  
    if (!lua_state[newState].valid()) {
    const std::string errMsg =
        "AI state: " + newState + " not found on change state method";
    throw std::runtime_error(errMsg);
    }
    
    m_previousState = m_currentState;                      // track previous state
    lua_state[m_currentState]["onExit"](*m_npcReference);    // execute exit code
    m_currentState = newState;                             // change states
    lua_state[m_currentState]["onEnter"](*m_npcReference);  // execute enter code of new state
}

std::filesystem::path& FSM::GetStatePath() 
{ 
    return m_statePath; 
}

void FSM::HandleMessage(sol::state& lua_state, const Message& msg)
{
    // first see if the current state is valid and that it can handle
    // the message
    if (lua_state[m_currentState]["onMessage"].valid()) {
        lua_state[m_currentState]["onMessage"](*m_npcReference, msg);
        return; // don't worry about the global if there is one
    }
    // if not, and if a global state has been implemented, send
    // the message to the global state
    if (lua_state[m_globalState]["onMessage"].valid()) {
        lua_state[m_globalState]["onMessage"](*m_npcReference, msg);
    }
}
