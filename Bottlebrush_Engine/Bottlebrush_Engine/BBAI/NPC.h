//
// Created by Alan 17/05/2024
//

#pragma once

#include <memory>

#include "FSM.h"
#include "Singleton.h"

class NPC 
{
public:
    NPC();
    virtual ~NPC();

    void initFSM(const std::filesystem::path& statesPath, const std::string& initialState);

    void Update();

    FSM<NPC>& GetFSM() { return m_FSM; }

private:
    FSM<NPC> m_FSM;
};