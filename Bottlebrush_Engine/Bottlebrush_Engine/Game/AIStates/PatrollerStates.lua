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
			if Message:GetEvent() == Event.PlayerSpotted then
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
		if not NPC:IsWaiting() then 
			FSM.ChangeState(NPC, "Patrol");
		end
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
			Dispatch.SendMessage("PlayerSpotted", NPC);
			FSM.ChangeState(NPC, "Chase");
		end	
	end,

	onExit = function(NPC)
		print("Exiting Patrol state");
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
		Movement.MoveTo(NPC, NPC:GetLastMoveTo());
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