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
	end,
	
	onMessage = function(NPC, Message)
		print("Message Received");
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
		Animation.SetAnimation(NPC, "stand");
	end,

	Update = function(NPC)
		if Detection.SeePlayer(NPC) then
			Dispatch.SendMessage("PlayerSpotted", NPC);
			FSM.ChangeState(NPC, "Chase");
		end	
	end,

	onExit = function(NPC)
		print("Exiting Idle state");
	end
}

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
Chase = {
	onEnter = function(NPC)
		print("Entered Chase state");
		Animation.SetAnimation(NPC, "run");
	end,

	Update = function(NPC)
		Movement.ChasePlayer(NPC) 
		if NPC:IsMoving() then
			Animation.SetAnimation(NPC, "run");
		elseif not NPC:IsMoving() then
			Animation.SetAnimation(NPC, "stand");
		end
		if not Detection.SeePlayer(NPC) then
			FSM.ChangeState(NPC, "Idle");
		end
	end,

	onExit = function(NPC)
		print("Exiting Chase state");
	end
}