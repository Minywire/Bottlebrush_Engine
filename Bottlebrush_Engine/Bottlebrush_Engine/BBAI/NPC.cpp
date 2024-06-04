//
// Created by Alan 17/05/2024
//

#include "NPC.h"
#include "Components.h"
#include "ECS.h"
#include "Entity.h"
#include "EventDispatcher.h"
#include "Singleton.h"

NPC::NPC(const std::filesystem::path& statesPath,
         const std::string& initialState, Entity& entity)
    : m_FSM(this, statesPath, initialState), 
    m_DeltaTime(0.f),
    m_Entity(entity),
    m_CurrentWaypoint(0),
    m_WaitTimeElapsed(0),
    m_PatrolWaitDuration(1),
    m_WaitTimerDuration(0),
    m_Moving(false)
{

}

void NPC::Update(sol::state& lua_state, float deltaTime) {
    m_DeltaTime = deltaTime;
	m_FSM.update(lua_state);

    if (IsWaiting() && !m_Moving) m_WaitTimeElapsed += m_DeltaTime;
}

void NPC::MoveTo(const glm::vec2& targetPos, ECS& ecs, float offset)
{
    // MoveTo returns true if it has reached that destination
    m_Moving = !Movement::MoveTo(GetVec2Position(ecs), targetPos, 
        m_current_speed, m_acceleration_rate, m_direction, m_DeltaTime, offset);

    // track last target pos
    m_LastMoveTo = targetPos;
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

    // waits for the timer duration and not moving
    if (!IsWaiting() && !m_Moving) 
    {
        m_WaitTimeElapsed = 0; // reset time elapsed
        m_CurrentWaypoint++; // move to next waypoint
    }
}

bool NPC::SeePlayer(const glm::vec2& targetPos, ECS& ecs, float coneDistance, float fov)
{
    return Movement::SeeTarget(GetVec2Position(ecs), targetPos, m_direction, coneDistance, fov);
}

void NPC::SendMessage(ECS& ecs, sol::state& lua_state, Message& msg)
{
    auto group = ecs.GetAllEntitiesWith<AIControllerComponent>();
    for (auto entity : group)
    {
        auto& aic = group.get<AIControllerComponent>(entity);
        auto& npc = aic.npc;

        // don't send a message to self
        if (entt::entity(m_Entity) == entity) continue;

        // send message to all NPCs through singleton EventDispatcher
        Singleton<EventDispatcher>::Instance().DispatchMessage(lua_state, msg, npc);
    }
}

bool NPC::IsMoving()
{
    return m_Moving;
}

void NPC::StopMoving()
{
    m_Moving = false;
    ClearWaitDuration();
}

glm::vec2 NPC::GetVec2Position(ECS& ecs) 
{
    // get transform
    const auto& transform = m_Entity.GetComponent<TransformComponent>(ecs.getReg());
    // get x and z position as vec2
    const glm::vec2 pos = {transform.position.x, transform.position.z};

    return pos;
}


glm::vec2& NPC::GetLastMoveTo()
{
    return m_LastMoveTo;
}

void NPC::SetWaitDuration(float wait)
{
    m_WaitTimerDuration = wait;
}

void NPC::ClearWaitDuration()
{
    m_WaitTimerDuration = 0;
    m_WaitTimeElapsed = 0;
}

bool NPC::IsWaiting()
{
    return m_WaitTimeElapsed < m_WaitTimerDuration;
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

Entity& NPC::GetEntity()
{
    return m_Entity;
}

FSM& NPC::GetFSM() 
{ 
	return m_FSM; 
}
