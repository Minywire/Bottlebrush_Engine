--Load all game entities from scripts here!
math.randomseed(os.time())

-- Globals
local CENTRE = 40960
local NUM_TREES = 1200
local NUM_HOUSE = 20
local NUM_WANDERER = 20
local NUM_IDLER = 10
local NUM_PATROLLER = 5

-- Functions
local function create_trees()
    local offset = 20000
    local min = CENTRE - offset
    local max = CENTRE + offset

    for i = 1, NUM_TREES, 1 do
        local x = math.random(min, max)
        local z = math.random(min, max)
        create_entityTR("Game/PineTree.lua", x, getTerrainHeight(x, z), z);
    end
end

local function create_house()
    local offset = 25000
    local min = CENTRE - offset
    local max = CENTRE + offset

    for i = 1, NUM_HOUSE, 1 do
        local x = math.random(min, max)
        local z = math.random(min, max)
        create_entityTR("Game/House.lua", x, getTerrainHeight(x, z), z);
    end
end

local function create_npc_wanderer()
    local offset = 6500
    local min = CENTRE - offset
    local max = CENTRE + offset

    for i = 1, NUM_WANDERER, 1 do
        local x = math.random(min, max)
        local z = math.random(min, max)
        create_entityTR("Game/NPCs/Wanderer1.lua", x, getTerrainHeight(x, z), z);
    end
end

local function create_npc_idler()
    local offset = 7500
    local min = CENTRE - offset
    local max = CENTRE + offset

    for i = 1, NUM_IDLER, 1 do
        local x = math.random(min, max)
        local z = math.random(min, max)
        create_entityTR("Game/NPCs/Idler1.lua", x, getTerrainHeight(x, z), z);
    end
end

-- Game Entities
create_entity("Game/Terrain/MainTerrain.lua");
create_entity("Game/MD2Models/necro.lua");
create_trees()
create_house()
create_npc_wanderer()
create_npc_idler()
create_entity("Game/NPCs/Patroller1.lua");
create_entity("Game/NPCs/Patroller2.lua");
create_entity("Game/exitCube.lua");
