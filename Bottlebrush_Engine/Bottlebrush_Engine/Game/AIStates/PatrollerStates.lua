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
		NPC:StopMoving();
		NPC:SetWaitDuration(5.0);
	end,

	Update = function(NPC)
		if not NPC:IsWaiting() then 
			FSM.ChangeState(NPC, "Patrol");
		end
		if Detection.SeePlayer(NPC) then
			FSM.ChangeState(NPC, "Chase");
		end	
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
		NPC:SetWaitDuration(3.0);
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
		if not Detection.SeePlayer(NPC) then
			FSM.ChangeState(NPC, "Idle");
		end
	end,

	onExit = function(NPC)
		print("Exiting Chase state");
	end
}