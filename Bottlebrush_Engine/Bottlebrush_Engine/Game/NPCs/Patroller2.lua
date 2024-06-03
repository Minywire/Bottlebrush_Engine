Entity = {
    Transform = {
        Position = {
            x = 400,
            y = 40,
            z = 450
        },
        Rotation = {
            x = 0,
            y = 0,
            z = 0
        },
        Scale = {
            x = 1,
            y = 1,
            z = 1
        }
    },
    MD2Model = {
        ModelPath = "Resources/MD2Models/Models/doomguy.md2",
        TexturePath = "Resources/MD2Models/Textures/doomguy.png"
    },
    AI = {
        StatesPath = "Game/AIStates/PatrollerStates.lua",
        InitialState = "Idle",
        Waypoints = {vec2(250, 100), vec2(600, 450), vec2(250, 600)}
    }
}