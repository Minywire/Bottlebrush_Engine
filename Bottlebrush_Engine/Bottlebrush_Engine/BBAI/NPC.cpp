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
    m_Entity(entity)
{

}

void NPC::Update(sol::state& lua_state, float deltaTime) 
{
    m_DeltaTimeAI = deltaTime;
	m_FSM.update(lua_state);
}

void NPC::MoveTo(float PosX, float PosZ)
{
    std::cout << "in moveTo func" << std::endl;

    glm::vec2 targetPos = glm::vec2(PosX, PosZ);
    // get transform
    auto& transform = m_Entity.GetComponent<TransformComponent>(m_ECS.getReg());
    glm::vec3& v3Pos = transform.position;
    glm::vec2 pos = {v3Pos.x, v3Pos.z};
    
    std::cout << "Current Pos x: " << v3Pos.x << " z: " << v3Pos.z << std::endl;

    // get movement
    auto& movement = m_Entity.GetComponent<MovementComponent>(m_ECS.getReg());
    glm::vec2& curVel = movement.direction;

    // call move to function
    m_Moving = !Movement::MoveTo(pos, targetPos, curVel, movement.current_speed, movement.acceleration_rate, m_DeltaTimeAI, 100.f);
    
    std::cout << "wants to move" << m_Moving << std::endl;
    //std::cout << "New Pos x: " << v3Pos.x << " z: " << v3Pos.z << std::endl;

    std::cout << "out moveTo func" << std::endl;
}


void NPC::MoveTo(glm::vec2 targetPos)
{
    std::cout << "in moveTo func" << std::endl;

    // get transform
    auto& transform = m_Entity.GetComponent<TransformComponent>(m_ECS.getReg());
    glm::vec3& v3Pos = transform.position;
    glm::vec2 pos = {v3Pos.x, v3Pos.z};
    
    std::cout << "Current Pos x: " << v3Pos.x << " z: " << v3Pos.z << std::endl;

    // get movement
    auto& movement = m_Entity.GetComponent<MovementComponent>(m_ECS.getReg());
    glm::vec2& curVel = movement.direction;

    // call move to function
    m_Moving = Movement::MoveTo(pos, targetPos, curVel, movement.current_speed, movement.acceleration_rate, m_DeltaTimeAI);

    //std::cout << "New Pos x: " << v3Pos.x << " z: " << v3Pos.z << std::endl;

    std::cout << "out moveTo func" << std::endl;
}

bool NPC::WantsToMove()
{
    return m_Moving;
}

FSM& NPC::GetFSM() 
{ 
	return m_FSM; 
}
