//
// Created by Alan 17/05/2024
//

#include "NPC.h"

NPC::NPC() : m_FSM(FSM<NPC>(this)) 
{

}

NPC::~NPC()
{

}

void NPC::initFSM(const std::filesystem::path& statesPath, const std::string& initialState) 
{
	m_FSM.SetStatePath(statesPath);
	m_FSM.SetCurrentState(initialState);
	m_FSM.SetPreviousState(initialState);

	std::cout << "State Path: " << statesPath.string() << std::endl; //@Debug Line, to be removed
	std::cout << "Initial State: " << initialState << std::endl; //@Debug Line, to be removed
}

void NPC::Update()
{
	m_FSM.update();
}
