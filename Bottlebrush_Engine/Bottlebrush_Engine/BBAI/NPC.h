//
// Created by Alan 17/05/2024
//

#pragma once

#include "FSM.h"
#include "Movement.h"
#include "Entity.h"
#include "Message.h"

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
    /// @param the acceptable range to be considered at targetpos
    void MoveTo(const glm::vec2& targetPos, ECS& ecs, float offset = 100);

    /// @author Alan
    /// @brief adds a waypoint to the member vector, used for patrolling
    /// @param point x and z vec2 of world coords
    void AddWaypoint(glm::vec2 point);
    
    /// @author Alan
    /// @brief Moves to all waypoints in member vector
    /// @param ecs register to get entity and its components
    void Patrol(ECS& ecs);

    /// @author Alan
    /// @brief Determine if NPC can see the player by a cone projection
    /// @param targetPos Player's position
    /// @param ecs register to retrieve NPC transform
    /// @param coneDistance the range distance of detection
    /// @param fov the width range of detection
    /// @return whether Player is standing within the cone
    bool SeePlayer(const glm::vec2& targetPos, ECS& ecs, float coneDistance, float fov);

    /// @author Alan
    /// @brief uses the EventDispatcher, and sends a message to all NPCs
    /// @param ecs register used to send a message to all NPCs
    /// @param lua_state passed onto FSM::HandleMessage()
    /// @param msg event message
    void SendMessage(ECS& ecs, sol::state& lua_state, Message& msg);
    
    /// @author Alan
    /// @brief see if NPC has movement input
    /// @return is NPC trying to move
    bool IsMoving();

    /// @author Alan
    /// @brief stops any movement input and clears wait timers
    void StopMoving();

    /// @author Alan
    /// @brief gets transform component and returns in position in (x,z) format
    /// @param ecs register to get transform component
    /// @return floor position (x,z)
    glm::vec2 GetVec2Position(ECS& ecs);

    /// @author Alan
    /// @brief set a wait timer
    /// @param wait duration in seconds
    void SetWaitDuration(float wait);

    /// @author Alan
    /// @brief clears wait timers
    void ClearWaitDuration();

    /// @author Alan
    /// @brief sees if there is a wait timer
    /// @return wait time > wait timer
    bool IsWaiting();

    /// @author Alan
    /// @brief gets the last movement command position
    /// @return a world coord
    glm::vec2& GetLastMoveTo();

    float& GetCurrentSpeed();

    float& GetMaxSpeed();

    float& GetAcceleration();

    float& GetDecceleration();

    glm::vec2& GetDirection();

    Entity& GetEntity();

    FSM& GetFSM();

private:
    FSM m_FSM;
    Entity m_Entity; // reference to this entity on construction

    float m_DeltaTime;  // time elasped for AI update call
    bool m_Moving; // bool for checking if NPC has movement input
    std::vector<glm::vec2> m_Waypoints;  // waypoints for patrolling
    int m_CurrentWaypoint; // tracking what is the current waypoint
    float m_WaitTimeElapsed; // its accumulated waiting time
    float m_PatrolWaitDuration;  // patrol max waiting duration
    float m_WaitTimerDuration;   // wait timer for miscellanenous reasons

    //movement properties
    float m_max_speed = 50.f;
    float m_current_speed = 0.f;
    float m_acceleration_rate = 0.1f;
    float m_deceleration_rate = 0.1f;
    glm::vec2 m_direction = {1.0f, 1.0f};  // direction that the NPC is facing

    glm::vec2 m_LastMoveTo = {0.0f, 0.0f};  // last move to location

    
};