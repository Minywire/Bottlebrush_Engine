--Load all game entities from scripts here!

create_entity("Game/Terrain/MainTerrain.lua");

create_entity("Game/Cube.lua");
create_entityTR("Game/NPC.lua", 500, 50, 450);
create_entityTR("Game/NPC.lua", 400, 40, 450);

create_entity("Game/MD2Models/doomguy.lua");

for start=0, 400, 100 do
    for start1=0, 400, 100 do
        create_entityTR("Game/PineTree.lua", start, 0, start1); --Create a grid of 16 instances
    end
end

for start=0, 400, 100 do
    for start1=0, 300, 100 do
        create_entityTR("Game/House.lua", start, 0, start1); --Create a grid of 12 instances
    end
end

create_entity("Game/exitCube.lua");
create_entity("Game/ico-sphere.lua");
