//
// Created by Alan 24/04/2024
//

#include "FSM.h"

class NPC {
public:
	NPC(FSM fsm);

	/// @author Alan
	/// @brief update in main game loop function
	void Update();

	/// @author Alan
	/// @brief calls the event handler for spotting the player
	void SpotPlayer();

	/// @author Alan
	/// @brief calls the event handler for when the AI loses the player
	void LosePlayer();

private:
	FSM m_fsm;

};
