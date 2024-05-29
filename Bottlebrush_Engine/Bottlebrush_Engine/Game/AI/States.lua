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
		NPC:AddWaypoint(vec2(150, 150));
		NPC:AddWaypoint(vec2(450, 450));
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
		NPC:Patrol();
	end,

	onExit = function(NPC)
		print("Exiting Patrol state");
	end
}