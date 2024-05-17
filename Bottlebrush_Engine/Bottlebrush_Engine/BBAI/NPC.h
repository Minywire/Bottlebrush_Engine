//
// Created by Alan 17/05/2024
//

#include <memory>

#include "FSM.h"

class NPC {
public:
    NPC();
    virtual ~NPC();

    void update();

private:
    std::unique_ptr<FSM<NPC>> m_FSM;
};