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
	end,

	Update = function(NPC)
		if Detection.SeePlayer(NPC) then
			Dispatch.SendMessage(Message(Event.PlayerSpotted, NPC));
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