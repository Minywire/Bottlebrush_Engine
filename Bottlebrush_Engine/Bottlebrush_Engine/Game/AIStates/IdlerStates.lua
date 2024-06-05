-------------------------------------------------------------------------------

-- create some useful animation functions just in Lua

-------------------------------------------------------------------------------

function setMovingAnimation(NPC)
	if Animation.GetAnimation(NPC) == "punch" then
		
	elseif NPC:IsMoving() then
		if Animation.GetAnimation(NPC) ~= "run" then
			Animation.SetAnimation(NPC, "run");
		end
	elseif not NPC:IsMoving() then
		if Animation.GetAnimation(NPC) ~= "stand" then
			Animation.SetAnimation(NPC, "stand");
		end
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
		if Detection.SeePlayer(NPC, 1000.0, 160.0) then
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			FSM.ChangeState(NPC, "Chase");
		end	
	end,

	onExit = function(NPC)
		NPC:ClearWaitDuration();
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
		if Detection.SeePlayer(NPC, 1000.0, 160.0) then
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			if not Movement.ChasePlayer(NPC) then
				FSM.ChangeState(NPC, "Attack");
			end
		elseif not Detection.SeePlayer(NPC, 1000.0, 160.0) and not NPC:IsMoving() then
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
		if Detection.SeePlayer(NPC, 1000.0, 160.0) then
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			FSM.ChangeState(NPC, "Chase");
		elseif not Detection.SeePlayer(NPC, 1000.0, 160.0) and not NPC:IsMoving() then
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

-------------------------------------------------------------------------------

-- create the attack state

-------------------------------------------------------------------------------
Attack = {
	onEnter = function(NPC)
		Animation.SetAnimation(NPC, "punch");
	end,

	Update = function(NPC)
		Game.GameOver();
	end,

	onExit = function(NPC)

	end,
}