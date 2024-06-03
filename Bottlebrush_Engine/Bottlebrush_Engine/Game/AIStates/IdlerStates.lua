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
		if Detection.InMessageRange(NPC, Message, 500.0) then
			print("Lua: Message Received");
			if Message:GetEvent() == "PlayerSpotted" then
				FSM.ChangeState(NPC, "Chase");
			else
				print("Lua: hasnt been spotted")
			end
		end
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
			Dispatch.SendMessage("PlayerSpotted", NPC);
			FSM.ChangeState(NPC, "Chase");
		end	
	end,

	onExit = function(NPC)
		print("Exiting Idle state");
		NPC:ClearWaitDuration();
	end
}

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
Chase = {
	onEnter = function(NPC)
		print("Entered Chase state");
		Movement.ChasePlayer(NPC);
	end,

	Update = function(NPC)
		Movement.MoveTo(NPC, NPC:GetLastPlayerLocation());
		if Detection.SeePlayer(NPC) then
			Movement.ChasePlayer(NPC);
			Dispatch.SendMessage("PlayerSpotted", NPC);
		elseif not Detection.SeePlayer(NPC) and not NPC:IsMoving() then
			FSM.ChangeState(NPC, "Idle");
		end
	end,

	onExit = function(NPC)
		print("Exiting Chase state");
	end
}