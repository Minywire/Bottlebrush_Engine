-------------------------------------------------------------------------------

-- create some useful animation functions just in Lua

-------------------------------------------------------------------------------

function setMovingAnimation(NPC)
	if NPC:IsMoving() then
		Animation.SetAnimation(NPC, "run");
	elseif not NPC:IsMoving() then
		Animation.SetAnimation(NPC, "stand");
	end
end

-------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
Global = {
	onEnter = function(NPC)
		
	end,

	Update = function(NPC)
		setMovingAnimation(NPC);
	end,

	onExit = function(NPC)
		
	end,

	onMessage = function(NPC, Message)
		
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
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			FSM.ChangeState(NPC, "Chase");
		end	
	end,

	onExit = function(NPC)
		NPC:ClearAllTimers();
	end,

	onMessage = function(NPC, Message)
		if Dispatch.InMessageRange(NPC, Message, 2000.0) then
			if Message.Event == "PlayerSpotted" then
				Movement.MoveTo(NPC, Dispatch.GetVec2SenderLocation(Message))
				FSM.ChangeState(NPC, "Investigate");
			end
		end
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
		Movement.Patrol(NPC)
		if Detection.SeePlayer(NPC) then
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			FSM.ChangeState(NPC, "Chase");
		end	
	end,

	onExit = function(NPC)
		NPC:ClearAllTimers();
	end,

	onMessage = function(NPC, Message)
		if Dispatch.InMessageRange(NPC, Message, 2000.0) then
			if Message.Event == "PlayerSpotted" then
				Movement.MoveTo(NPC, Dispatch.GetVec2SenderLocation(Message))
				FSM.ChangeState(NPC, "Investigate");
			end
		end
	end
}

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
Chase = {
	onEnter = function(NPC)
		Movement.ChasePlayer(NPC);
	end,

	Update = function(NPC)
		Movement.MoveTo(NPC, NPC:GetLastMoveTo());
		if Detection.SeePlayer(NPC) then
			Movement.ChasePlayer(NPC);
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
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

	end,

	Update = function(NPC)
		Movement.MoveTo(NPC, NPC:GetLastMoveTo());
		if Detection.SeePlayer(NPC) then
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			FSM.ChangeState(NPC, "Chase");
		elseif not Detection.SeePlayer(NPC) and not NPC:IsMoving() then
			FSM.ChangeState(NPC, "Idle");
		end
	end,

	onExit = function(NPC)

	end,

	onMessage = function(NPC, Message)
		if Dispatch.InMessageRange(NPC, Message, 2000.0) then
			if Message.Event == "PlayerSpotted" then
				Movement.MoveTo(NPC, Dispatch.GetVec2SenderLocation(Message))
			end
		end
	end
}