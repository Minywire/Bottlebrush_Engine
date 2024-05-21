//
// Created by Alan 17/05/2024
//

#include "NPC.h"

NPC::NPC() : m_FSM(Singleton<FSM<NPC>>::Instance(this)) 
{

}

NPC::~NPC()
{

}

void NPC::initFSM(const std::filesystem::path& statesPath) 
{
	m_FSM.SetStatePath(statesPath);
}

void NPC::Update()
{
	m_FSM.update();
}
