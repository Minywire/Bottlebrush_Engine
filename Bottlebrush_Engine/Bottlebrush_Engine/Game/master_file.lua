--Load all game entities from scripts here!

create_entity("Game/GrassCube.lua");

for start=0, 5000, 1000 do
    for start1=0, 5000, 1000 do
        create_entityTR("Game/PineTree.lua", 3750 + start, 0, 2500 + start1); --Create a line of 10 instances
    end
end


