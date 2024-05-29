//
// Created by Alan 17/05/2024
//

#include "NPC.h"
#include "Components.h"
#include "ECS.h"
#include "Entity.h"

NPC::NPC(const std::filesystem::path& statesPath,
         const std::string& initialState, ECS& ecs, Entity& entity)
    : m_FSM(this, statesPath, initialState), 
    m_DeltaTimeAI(0.f),
    m_ECS(ecs), 
    m_Entity(entity),
    m_CurrentWaypoint(0)
{

}

void NPC::Update(sol::state& lua_state, float deltaTime) 
{
    m_DeltaTimeAI = deltaTime;
	m_FSM.update(lua_state);
}

void NPC::MoveTo(const glm::vec2& targetPos)
{
    // get transform
    auto& transform = m_Entity.GetComponent<TransformComponent>(m_ECS.getReg());
    // get x and z position as vec2
    glm::vec2 pos = {transform.position.x, transform.position.z};

    // get movement
    auto& movement = m_Entity.GetComponent<MovementComponent>(m_ECS.getReg());

    // call move to function
    m_Moving = !Movement::MoveTo(pos, targetPos, movement.direction, 
        movement.current_speed, m_DeltaTimeAI);
}

void NPC::AddWaypoint(glm::vec2 point)
{
    m_Waypoints.push_back(point);
}

void NPC::Patrol()
{
    if (m_Waypoints.size() == 0) return;
    if (m_CurrentWaypoint >= m_Waypoints.size()) m_CurrentWaypoint = 0;

    MoveTo(m_Waypoints[m_CurrentWaypoint]);

    if (!m_Moving) m_CurrentWaypoint++;
}

bool NPC::IsMoving()
{
    return m_Moving;
}

FSM& NPC::GetFSM() 
{ 
	return m_FSM; 
}
