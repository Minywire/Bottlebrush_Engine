Entity = {
    Transform = {
        Position = {
            x = 0,
            y = 0,
            z = 0
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
        StatesPath = "Game/AIStates/States.lua",
        InitialState = "Wander",
        GlobalState = "Global"
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