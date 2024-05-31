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
            x = 10,
            y = 10,
            z = 10
        }
    },
    Model = {
        ModelPath = "Resources/Models/D20.obj",
        MaterialPath = "Resources/Models/Disabled_Pokemon_Go_-_Eevee___Zubat_0-3_screenshot.png"
    },
    AI = {
        StatesPath = "Game/AIStates/States.lua",
        InitialState = "Patrol",
        Waypoints = {vec2(150, 150), vec2(450, 450)}
    }
}