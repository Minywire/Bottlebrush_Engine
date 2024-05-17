-------------------------------------------------------------------------------

-- create the global state

-------------------------------------------------------------------------------
state_global = {}


state_global["enter"] = function(player)
	print("entered global state")


end


state_global["execute"] = function(player)
	print("in global state")


end

  
state_global["exit"] = function(player)
	print("exited global state")


end

state_global["onEvent"] = function(player,event)

return false

end

-------------------------------------------------------------------------------

-- create the idle state

-------------------------------------------------------------------------------
state_idle = {}

state_idle["onEnter"] = function(player)
	print("entered idle state")

end

state_idle["update"] = function(player)
	print("in idle state")

end
  
state_idle["onExit"] = function(player)
	print("executing idle state")

end

-------------------------------------------------------------------------------

-- create the patrol state

-------------------------------------------------------------------------------
state_patrol = {}


state_patrol["onEnter"] = function(player)
	print ("enter patrol state")
  
end


state_patrol["update"] = function(player)
	print ("in patrol state")

end

  
state_patrol["onExit"] = function(player)
	print ("exit patrol state")

end


