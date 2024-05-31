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
        ModelPath = "Resources/Models/cube.obj",
        MaterialPath = "Resources/Models/Disabled_Pokemon_Go_-_Eevee___Zubat_0-3_screenshot.png"
    },
    AI = {
        StatesPath = "Game/AIStates/States.lua",
        InitialState = "Patrol",
        Waypoints = {vec2(250, 100), vec2(600, 450), vec2(250, 600)}
    }
}