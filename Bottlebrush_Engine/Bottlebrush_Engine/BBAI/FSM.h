//
// Created by Alan 24/04/2024
//

#include "State.h"

/// @author Alan
/// @brief Finite State Machine for NPCs
template <typename entity_type>
class FSM
{
public:
  FSM(entity_type* FSMowner);
  virtual ~FSM();

  void update() const;

  void changeState(State<entity_type>* newState); // @TODO find lua object to replace State<entity_type>

  void revertToPreviousState();

  bool isInState(const State<entity_type>& st) const;

  // set states
  void setPreviousState(const State<entity_type>* st); // @TODO find lua object to replace State<entity_type>
  void setCurrentState(const State<entity_type>* st);
  void setGlobalState(const State<entity_type>* st);

  State<entity_type>& getPreviousState();
  State<entity_type>& getCurrentState();
  State<entity_type>& getGlobalState();

private:
	entity_type* m_owner; // owning AI object
	
	State<entity_type>* m_previousState; // @TODO find lua object to replace State<entity_type>
	State<entity_type>*	m_globalState;
	State<entity_type>* m_currentState;
};
