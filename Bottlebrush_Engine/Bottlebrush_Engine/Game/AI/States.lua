-------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
Global = {
	onEnter = function(NPC)
		print("Entered Global state");
	end,

	Update = function(NPC)
		print("in global state");

	end,

	onExit = function(NPC)
		print("Exiting Global state");
	end
}

-------------------------------------------------------------------------------

-- create the idle state

-------------------------------------------------------------------------------
Idle = {
	onEnter = function(NPC)
		print("Entered Idle state");
	end,

	Update = function(NPC)
		print("in idle state");
		FSM.ChangeState(NPC, "Patrol");

	end,

	onExit = function(NPC)
		print("Exiting Idle state");
	end
}

-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
Patrol = {
	onEnter = function(NPC)
		print("Entered Patrol state");
	end,

	Update = function(NPC)
		print ("in patrol state");
		NPC:MoveTo(vec2(150.0, 150.0));
	end,

	onExit = function(NPC)
		print("Exiting Patrol state");
	end
}