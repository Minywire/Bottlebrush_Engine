-------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
Global = {
	onEnter = function(NPC)
		print("Entered Global state");
	end,

	Update = function(NPC)

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
		Movement.Patrol(NPC);
		if Detection.SeePlayer(NPC) then
			FSM.ChangeState(NPC, "Chase");
		end	
	end,

	onExit = function(NPC)
		print("Exiting Patrol state");
	end
}

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
Chase = {
	onEnter = function(NPC)
		print("Entered Chase state");
	end,

	Update = function(NPC)
		Movement.ChasePlayer(NPC);
	end,

	onExit = function(NPC)
		print("Exiting Chase state");
	end
}