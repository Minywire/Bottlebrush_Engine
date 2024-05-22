-------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
Global = {
	onEnter = function(player)
		print("entered global state")

	end,

	Update = function(player)
		print("in global state")

	end,

  
	onExit = function(player)
		print("exited global state")

	end,
}

-------------------------------------------------------------------------------

-- create the idle state

-------------------------------------------------------------------------------
Idle = {
	onEnter = function(player)
		print("entered idle state")

	end,

	Update = function(player)
		print("in idle state")

	end,
  
	onExit = function(player)
		print("executing idle state")

	end
}



-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
Patrol = {
	onEnter = function(player)
		print ("enter patrol state")
  
	end,

	Update = function(player)
		print ("in patrol state")

	end,

	onExit = function(player)
		print ("exit patrol state")

	end
}





