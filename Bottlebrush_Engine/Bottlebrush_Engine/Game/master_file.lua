--Load all game entities from scripts here!

create_entity("Game/Terrain/MainTerrain.lua");

create_entity("Game/Cube.lua");
create_entityTR("Game/NPC.lua", 500, 30, 450);
create_entityTR("Game/NPC.lua", 400, 20, 450);

for start=0, 4000, 1000 do
    for start1=0, 4000, 1000 do
        create_entityTR("Game/PineTree.lua", 4750 + start, 0, 2500 + start1); --Create a grid of 16 instances
    end
end

for start=0, 4000, 1000 do
    for start1=0, 3000, 1000 do
        create_entityTR("Game/House.lua", 5500 + start, 0, 2650 + start1); --Create a grid of 12 instances
    end
end

--for start=0, 2000, 1000 do
--    for start1=0, 3000, 1000 do
--        create_entity("Game/Rock1.lua", 3250 + start, 0, 1143 + start1); --Create a grid of 6 instances
--    end
--end

create_entity("Game/exitCube.lua");
create_entity("Game/ico-sphere.lua");
