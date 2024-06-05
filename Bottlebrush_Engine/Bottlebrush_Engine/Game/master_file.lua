--Load all game entities from scripts here!

create_entity("Game/Terrain/MainTerrain.lua");
create_entity("Game/MD2Models/doomguy.lua");

math.randomseed(os.time())
local centre = 40960

local offset = 30000
local min = centre - offset
local max = centre + offset
local increment = 1000

for i = min, max, increment do
    for j = min, max, increment do
        local random_x = math.random(500)
        local random_z = math.random(500)
        local x = i + random_x
        local z = j - random_z
        create_entityTR("Game/PineTree.lua", x, getTerrainHeight(x, z), z);
    end
end

for i = min, max, 4 * increment do
    for j = min, max, 4 * increment do
        local random_x = math.random(500)
        local random_z = math.random(500)
        local x = i - random_x
        local z = j + random_z
        create_entityTR("Game/House.lua", x, getTerrainHeight(x, z), z);
    end
end

local offset = 10000
local min = centre - offset
local max = centre + offset
local range = max - min
local sqrt_num_wanderer = 12
local sqrt_num_idler = 3
local sqrt_num_patrollers = 4

for i = min, max, range / sqrt_num_wanderer do
    for j = min, max, range / sqrt_num_wanderer do
        create_entityTR("Game/NPCs/Wanderer1.lua", i, getTerrainHeight(i, j), j);
    end
end

for i = min, max, range / sqrt_num_idler do
    for j = min, max, range / sqrt_num_idler do
        create_entityTR("Game/NPCs/Idler1.lua", i, getTerrainHeight(i, j), j);
    end
end

create_entity("Game/NPCs/Patroller1.lua");
create_entity("Game/NPCs/Patroller2.lua");

create_entity("Game/exitCube.lua");
