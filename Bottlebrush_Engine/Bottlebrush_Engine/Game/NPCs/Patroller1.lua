Entity = {
    Transform = {
        Position = {
            x = 500,
            y = 50,
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
        Waypoints = {vec2(150, 150), vec2(450, 450)}
    }
}