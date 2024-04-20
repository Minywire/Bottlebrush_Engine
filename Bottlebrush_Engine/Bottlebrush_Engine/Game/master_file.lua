--Load all game entities from scripts here!

create_entity("Game/GrassCube.lua");

for start=0, 4000, 1000 do
    for start1=0, 4000, 1000 do
        create_entityTR("Game/PineTree.lua", 4750 + start, 0, 2500 + start1); --Create a grid of 16 instances
    end
end

--for start=0, 5000, 1000 do
--    for start1=0, 3000, 1000 do
--        create_entityTR("Game/House.lua", 6000 + start, 0, 4550 + start1); --Create a grid of 15 instances
--    end
--end


