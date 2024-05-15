//
// Created by Alan 15/05/2024
//

#pragma once

/// @brief abstract class that defines how states of an FSM is structured
/// @tparam entity_type 
template <typename entity_type>
class State
{
public:
  

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
  friend class Singleton<State>; // allows singleton to access the private ctor
  State() {}
  virtual ~State() {}
};
