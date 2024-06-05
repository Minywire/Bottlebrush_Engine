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
            x = 0.6,
            y = 0.6,
            z = 0.6
        }
    },
    MD2Model = {
        ModelPath = "Resources/MD2Models/Models/necro.md2",
        TexturePath = "Resources/MD2Models/Textures/necro.png"
    },
    AI = {
        StatesPath = "Game/AIStates/PatrollerStates.lua",
        InitialState = "Idle",
        Waypoints = {vec2(41500, 42500), vec2(42300, 42000), vec2(44000, 41000)}
    }
}