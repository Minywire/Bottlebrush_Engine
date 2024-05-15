//
// Created by Alan 15/05/2024
//

#pragma once

/// @author Alan
/// @brief abstract class that defines how states of an FSM is structured
/// @tparam entity_type 
template <typename entity_type>
class State
{
public:
  
	/// @author Alan
	/// @brief executes when the state is entered
	/// @param AI object
	virtual void onEnter(entity_type*) = 0;
	/// @brief normal update function per tick
	/// @param AI object
	virtual void Update(entity_type*) = 0;
	/// @brief executes when the state is exited
	/// @param AI object
	virtual void onExit(entity_type*) = 0;

protected:
	/// @author Alan
	/// @brief allows singleton to access the private ctor
	/// forces users to access states through singleton pattern
	friend class Singleton<State>; 

	State() {}
	virtual ~State() {}
};
