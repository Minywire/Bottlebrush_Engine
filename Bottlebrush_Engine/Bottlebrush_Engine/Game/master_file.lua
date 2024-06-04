--Load all game entities from scripts here!

create_entity("Game/Terrain/MainTerrain.lua");

create_entity("Game/Cube.lua");
create_entity("Game/NPCs/Patroller1.lua");
create_entity("Game/NPCs/Patroller2.lua");
create_entity("Game/NPCs/Idler1.lua");

create_entity("Game/MD2Models/doomguy.lua");

for start=0, 4000, 1000 do
    for start1=0, 4000, 1000 do
        create_entityTR("Game/PineTree.lua", start, getTerrainHeight(start, start1), start1); --Create a grid of 16 instances
    end
end

for start=0, 4000, 1000 do
    for start1=0, 3000, 1000 do
       create_entityTR("Game/House.lua", start, getTerrainHeight(start,start1), start1); --Create a grid of 12 instances
    end
end

create_entity("Game/exitCube.lua");
create_entity("Game/ico-sphere.lua");
