-------------------------------------------------------------------------------

-- create some useful animation functions just in Lua

-------------------------------------------------------------------------------

function setMovingAnimation(NPC)
	if Animation.GetAnimation(NPC) == "attack" then
		
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
WandererGlobal = {
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
WandererIdle = {
	onEnter = function(NPC)
		NPC:StopMoving();
		NPC:SetWaitDuration(5.0);
	end,

	Update = function(NPC)
		if not NPC:IsWaiting() then 
			FSM.ChangeState(NPC, "WandererWander");
		end
		if Detection.SeePlayer(NPC, 1000.0, 160.0) then
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			FSM.ChangeState(NPC, "WandererChase");
		end	
	end,

	onExit = function(NPC)
		NPC:ClearAllTimers();
	end,

	onMessage = function(NPC, Message)
		if Dispatch.InMessageRange(NPC, Message, 2000.0) then
			if Message.Event == "PlayerSpotted" then
				Movement.MoveTo(NPC, Dispatch.GetVec2SenderLocation(Message))
				FSM.ChangeState(NPC, "WandererInvestigate");
			end
		end
	end
}

-------------------------------------------------------------------------------

-- create the Wander state

-------------------------------------------------------------------------------
WandererWander = {
	onEnter = function(NPC)
		NPC:SetWander(200.0, 300.0, 50.0);
		Movement.Wander(NPC);
		NPC:SetWaitDuration(3.0);
	end,

	Update = function(NPC)
		Movement.MoveTo(NPC, NPC:GetLastMoveTo());
		if not NPC:IsWaiting() and not NPC:IsMoving() then
			NPC:ClearWaitTimeElapsed();
			Movement.Wander(NPC);
		end
		if Detection.SeePlayer(NPC, 1000.0, 160.0) then
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			FSM.ChangeState(NPC, "WandererChase");
		end	
	end,

	onExit = function(NPC)
		NPC:ClearAllTimers();
	end,

	onMessage = function(NPC, Message)
		if Dispatch.InMessageRange(NPC, Message, 1000.0) then
			if Message.Event == "PlayerSpotted" then
				Movement.MoveTo(NPC, Dispatch.GetVec2SenderLocation(Message))
				FSM.ChangeState(NPC, "WandererInvestigate");
			end
		end
	end
}

-------------------------------------------------------------------------------

-- create the chase state

-------------------------------------------------------------------------------
WandererChase = {
	onEnter = function(NPC)
		Movement.ChasePlayer(NPC);
		
	end,

	Update = function(NPC)
        Movement.MoveTo(NPC, NPC:GetLastMoveTo());
        if Detection.SeePlayer(NPC, 1000.0, 160.0) then
            Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
            if not Movement.ChasePlayer(NPC) then
                FSM.ChangeState(NPC, "WandererAttack");
            end
        elseif not Detection.SeePlayer(NPC, 1000.0, 160.0) and not NPC:IsMoving() then
            FSM.ChangeState(NPC, "WandererIdle");
        end
    end,

	onExit = function(NPC)
		
	end
}

-------------------------------------------------------------------------------

-- create the investigate state

-------------------------------------------------------------------------------
WandererInvestigate = {
	onEnter = function(NPC)
		
	end,

	Update = function(NPC)
		Movement.MoveTo(NPC, NPC:GetLastMoveTo());
		if Detection.SeePlayer(NPC, 1000.0, 160.0) then
			Dispatch.SendMessage("PlayerSpotted", NPC, 3.0);
			FSM.ChangeState(NPC, "WandererChase");
		elseif not Detection.SeePlayer(NPC, 1000.0, 160.0) and not NPC:IsMoving() then
			FSM.ChangeState(NPC, "WandererIdle");
		end
	end,

	onExit = function(NPC)

	end,

	onMessage = function(NPC, Message)
		if Dispatch.InMessageRange(NPC, Message, 1000.0) then
			if Message.Event == "PlayerSpotted" then
				Movement.MoveTo(NPC, Dispatch.GetVec2SenderLocation(Message))
			end
		end
	end
}

-------------------------------------------------------------------------------

-- create the attack state

-------------------------------------------------------------------------------
WandererAttack = {
    onEnter = function(NPC)
        Animation.SetAnimation(NPC, "attack");
    end,

    Update = function(NPC)
        Game.GameOver();
		if Movement.ChasePlayer(NPC) then
            FSM.ChangeState(NPC, "WandererChase");
        end
    end,

    onExit = function(NPC)
		Animation.SetAnimation(NPC, "run");
    end,
}