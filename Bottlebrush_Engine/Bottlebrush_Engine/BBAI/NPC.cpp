//
// Created by Alan 17/05/2024
//


#include "NPC.h"
NPC::NPC()
{
    m_FSM = std::make_unique<FSM<NPC>>(FSM<NPC>(this));
}

NPC::~NPC()
{

}
void NPC::update()
{
    m_FSM->update();
}
