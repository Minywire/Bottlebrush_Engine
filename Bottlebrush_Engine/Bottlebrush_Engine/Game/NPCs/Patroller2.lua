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
        InitialState = "PatrollerIdle",
        GlobalState = "PatrollerGlobal",
        Waypoints = {vec2(44100, 41500), vec2(42500, 44600)}
    },
    Collider = {
        Type = 0,
        IsStatic = 0,
        HalfExtents = {
            x = 5.0,
            y = 7.5,
            z = 5.0
        }
    }
}