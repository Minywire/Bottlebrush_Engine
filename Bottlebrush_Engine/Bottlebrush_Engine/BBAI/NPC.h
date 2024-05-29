//
// Created by Alan 17/05/2024
//

#pragma once

#include "FSM.h"
#include "Movement.h"
#include "Entity.h"

/** forward decl to avoid circle linking */
class ECS;

/// @author Alan
/// @brief NPC class that holds an FSM to determine it's states and transitions
/// This class will incorporate game functions such as movement and sensory methods
class NPC 
{
public:
    NPC(const std::filesystem::path& statesPath, const std::string& initialState,
        ECS& ecs, Entity& entity);
    
    /// @author Alan
    /// @brief update call for FSM
    /// @param lua_state ai script to read from
    void Update(sol::state& lua_state, float deltaTime);

    /// @author Alan
    /// @brief move to a position
    /// @param PosX x world coords
    /// @param PosZ z world coords
    void MoveTo(float PosX, float PosZ);

    /// @author Alan
    /// @brief move to a position
    /// @param targetPos vec2 of x and z world coords
    void MoveTo(const glm::vec2& targetPos);

    /// @author Alan
    /// @brief see if NPC has movement input
    /// @return is NPC trying to move
    bool IsMoving();

    FSM& GetFSM();

private:
    FSM m_FSM;
    ECS& m_ECS; // reference to the ECS
    Entity m_Entity; // reference to this entity on construction

    float m_DeltaTimeAI; // time elasped for AI update call
    bool m_Moving; // bool for checking if NPC has movement input
};