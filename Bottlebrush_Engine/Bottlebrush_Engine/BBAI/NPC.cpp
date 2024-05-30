//
// Created by Alan 17/05/2024
//

#include "NPC.h"
#include "Components.h"
#include "ECS.h"
#include "Entity.h"

NPC::NPC(const std::filesystem::path& statesPath,
         const std::string& initialState, Entity& entity)
    : m_FSM(this, statesPath, initialState), 
    m_AIUpdateIntervalTime(0.f),
    m_Entity(entity),
    m_CurrentWaypoint(0),
    m_WaitTimeElapsed(0),
    m_PatrolWaitDuration(1)
{

}

void NPC::Update(sol::state& lua_state, float AIUpdateIntervalTime) {
    m_AIUpdateIntervalTime = AIUpdateIntervalTime;
	m_FSM.update(lua_state);
}

void NPC::MoveTo(const glm::vec2& targetPos, ECS& ecs)
{
    // get transform
    auto& transform = m_Entity.GetComponent<TransformComponent>(ecs.getReg());
    // get x and z position as vec2
    glm::vec2 pos = {transform.position.x, transform.position.z};

    // call move to function
    m_Moving = !Movement::MoveTo(pos, targetPos, m_current_speed, m_acceleration_rate, m_direction, m_AIUpdateIntervalTime);
}

void NPC::AddWaypoint(glm::vec2 point)
{
    m_Waypoints.push_back(point);
}

void NPC::Patrol(ECS& ecs)
{
    if (m_Waypoints.size() == 0) return;
    if (m_CurrentWaypoint >= m_Waypoints.size()) m_CurrentWaypoint = 0;

    MoveTo(m_Waypoints[m_CurrentWaypoint], ecs);

    if (m_Moving) return;

    m_WaitTimeElapsed += m_AIUpdateIntervalTime;
    // waits for a duration
    if (m_WaitTimeElapsed > m_PatrolWaitDuration) {
        m_CurrentWaypoint++; // move to next waypoint
        m_WaitTimeElapsed = 0;
    }
}

bool NPC::IsMoving()
{
    return m_Moving;
}

float& NPC::GetCurrentSpeed()
{
    return m_current_speed;
}

float& NPC::GetMaxSpeed()
{
    return m_max_speed;
}

float& NPC::GetAcceleration()
{
    return m_acceleration_rate;
}

float& NPC::GetDecceleration()
{
    return m_deceleration_rate;
}

glm::vec2& NPC::GetDirection()
{
    return m_direction;
}

FSM& NPC::GetFSM() 
{ 
	return m_FSM; 
}
