//
// Created by Alan 17/05/2024
//

#include "NPC.h"

NPC::NPC(const std::filesystem::path& statesPath,
         const std::string& initialState, sol::state& lua_state)
    : m_FSM(this, statesPath, initialState, lua_state) {

}

/*
void NPC::update()
{
	m_FSM.update();
}
*/
FSM& NPC::getFSM() 
{ 
	return m_FSM; 
}
