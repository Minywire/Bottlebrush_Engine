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
		if Detection.SeePlayer(NPC) then
			print ("Seen in lua")
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
	end,

	Update = function(NPC)
		
	end,

	onExit = function(NPC)
		print("Exiting Patrol state");
	end
}