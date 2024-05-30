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
    m_DeltaTimeAI(0.f),
    m_Entity(entity),
    m_CurrentWaypoint(0),
    m_WaitTimeElapsed(0),
    m_PatrolWaitDuration(10)
{

}

void NPC::Update(sol::state& lua_state, float deltaTime) 
{
    m_DeltaTimeAI = deltaTime;
	m_FSM.update(lua_state);
}

void NPC::MoveTo(const glm::vec2& targetPos, ECS& ecs)
{
    // get transform
    auto& transform = m_Entity.GetComponent<TransformComponent>(ecs.getReg());
    // get x and z position as vec2
    glm::vec2 pos = {transform.position.x, transform.position.z};

    // get movement
    auto& movement = m_Entity.GetComponent<MovementComponent>(ecs.getReg());

    // call move to function
    m_Moving = !Movement::MoveTo(pos, targetPos, movement, m_DeltaTimeAI);
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

    m_WaitTimeElapsed++;
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

FSM& NPC::GetFSM() 
{ 
	return m_FSM; 
}
