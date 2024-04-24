//
// Created by Alan 24/04/2024
//

/// @author
/// @brief states that the FSM can be in
enum class FSMState {
	IDLE,
	PATROL,
	SEEK,
	CHASE,
};

/// @author Alan
/// @brief Events that can occur
enum class FSMEvent {
	PlayerSpotted,
	PlayerLost,
	PatrolMode
};

/// @author Alan
/// @brief Finite State Machine for NPCs
class FSM
{
public:
  FSM();

  /// @author Alan
  /// @brief event handler for when different events occur
  /// @param event is the type of event that occurred
  void HandleEvent(FSMEvent event);

  FSMState GetCurrentState() const;

private:
  FSMState m_currentState;
};
