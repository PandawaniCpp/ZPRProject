/**
    @date	03.04.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once

// Represents phase of the game.
namespace States {
    enum ID {
        NONE = 0,
        TITLE = 1,
        MENU = 1 << 1,
        LOAD = 1 << 2,
        GAME = 1 << 3,
        PAUSE = 1 << 4,
        EXIT = 1 << 5,
        LIMIT
    };
}

// List of all textures in the game.
namespace Textures {
    enum PLAYER {
        P_INIT,
        P_IDLE,		
        P_WALK,
        P_RUN,
        P_END
    };

    enum CREATURES {
        C_INIT,
        C_ZOMBIE,
        C_END
    };

    enum ITEMS {
        I_INIT,
        I_WALL,
        I_END
    };

    enum ANIMATIONS {
        A_INIT,
        A_LOADING_ANIM,
        A_END
    };
}

// List of all differen font used in the game.
namespace Fonts {
    enum ID {
        F_MENU,
        F_CONSOLE,
        FONTS_COUNT
    };
}

// List of all shader effects in the game.
namespace Effects {
    enum ID {
        TORCH_LIGHT,
        EFFECTS_COUNT
    };
}

// Identifiers for all game entities.
namespace Entities {
    enum ID {
        NONE,
        PLAYER,
        WALL,
        PREDATOR,
        HERBIVORE,
        ZOMBIE,
        
        VISION_RANGE,
        PLANT,
        ENTITIES_COUNT
    };
}

// Command identifiers
namespace Commands {
    enum ID {
        NONE,
        PRESS_ANY_KEY,
        G_EXIT,
        G_PAUSE,
        G_RESUME,
        CON_TRIGGER,
        RES_UP,
        RES_DOWN,
        SET_FULLSCREEN,
        SAVE_MAP_TO_IMG,
        START_SIMULATION,

        MOVE_FORWARD,
        STOP_FORWARD,
        MOVE_BACKWARD,
        STOP_BACKWARD,
        MOVE_LEFT,
        STOP_LEFT,
        MOVE_RIGHT,
        STOP_RIGHT,
        START_RUN,
        STOP_RUN,

        COMMANDS_COUNT
    };
}
