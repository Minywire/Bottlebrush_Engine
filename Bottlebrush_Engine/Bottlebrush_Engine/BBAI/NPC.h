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
    NPC(const std::filesystem::path& statesPath, const std::string& initialState, Entity& entity);
    
    /// @author Alan
    /// @brief update call for FSM
    /// @param lua_state ai script to read from
    /// @param AIUpdateIntervalTime is the time between ai update calls
    void Update(sol::state& lua_state, float AIUpdateIntervalTime);

    /// @author Alan
    /// @brief move to a position
    /// @param targetPos vec2 of x and z world coords
    /// @param ecs the register to get entity and its components
    void MoveTo(const glm::vec2& targetPos, ECS& ecs);

    /// @author Alan
    /// @brief adds a waypoint to the member vector, used for patrolling
    /// @param point x and z vec2 of world coords
    void AddWaypoint(glm::vec2 point);
    
    /// @author Alan
    /// @brief Moves to all waypoints in member vector
    /// @param ecs register to get entity and its components
    void Patrol(ECS& ecs);

    /// @author Alan
    /// @brief see if NPC has movement input
    /// @return is NPC trying to move
    bool IsMoving();

    float& GetCurrentSpeed();

    float& GetMaxSpeed();

    float& GetAcceleration();

    float& GetDecceleration();

    glm::vec2& GetDirection();

    FSM& GetFSM();

private:
    FSM m_FSM;
    Entity m_Entity; // reference to this entity on construction

    float m_AIUpdateIntervalTime;  // time elasped for AI update call
    bool m_Moving; // bool for checking if NPC has movement input
    std::vector<glm::vec2> m_Waypoints;  // waypoints for patrolling
    int m_CurrentWaypoint; // tracking what is the current waypoint
    float m_WaitTimeElapsed; // its accumulated waiting time
    float m_PatrolWaitDuration;  // patrol max waiting duration

    //movement properties
    float m_max_speed = 100.f;
    float m_current_speed = 0.f;
    float m_acceleration_rate = 0.1f;
    float m_deceleration_rate = 0.1f;
    glm::vec2 m_direction = {1, 1}; // direction that the NPC is facing
};