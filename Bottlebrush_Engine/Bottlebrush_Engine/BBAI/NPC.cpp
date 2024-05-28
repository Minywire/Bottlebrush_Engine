//
// Created by Alan 17/05/2024
//

#include "NPC.h"

NPC::NPC(const std::filesystem::path& statesPath, const std::string& initialState) : m_FSM(this, statesPath, initialState) 
{

}

void NPC::Update(sol::state & lua_state) 
{
	m_FSM.update(lua_state);
}

FSM& NPC::GetFSM() 
{ 
	return m_FSM; 
}
