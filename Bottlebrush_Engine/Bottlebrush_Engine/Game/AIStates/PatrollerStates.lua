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
		print("Messaged")
		--if Dispatch.InMessageRange(NPC, Message, 1000.0) then
			if Message:GetEvent() == "PlayerSpotted" then
				Movement.MoveTo(NPC, Dispatch.GetSenderLocation(Message))
				FSM.ChangeState(NPC, "Investigate");
			end
		--end
	end
}

-------------------------------------------------------------------------------

-- create the idle state

-------------------------------------------------------------------------------
Idle = {
	onEnter = function(NPC)
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

	end
}

-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
Patrol = {
	onEnter = function(NPC)
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
		NPC:ClearWaitDuration();
	end
}

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
Chase = {
	onEnter = function(NPC)
		print("Chasing")
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

	end
}

-------------------------------------------------------------------------------

-- create the investigate state

-------------------------------------------------------------------------------
Investigate = {
	onEnter = function(NPC)
		print("Investigate")
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

	end
}