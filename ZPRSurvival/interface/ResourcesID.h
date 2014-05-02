/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once

// Represents phase of the game.
namespace GameState {
	enum ID {
		INIT = 1,
		INTRO = 1 << 1, 
		IN_MENU = 1 << 3,
		PLAYING = 1 << 4, 
		PAUSE = 1 << 5, 
		EXIT = 1 << 6,
	};
}


// List of all textures in the game.
namespace Textures {
	enum PLAYER {
		P_INIT,
		P_IDLE,		
		P_WALK,
		P_END
	};

	enum CREATURES {
		C_INIT,
		C_WOLF,
		C_END
	};

	enum ITEMS {
		I_INIT,
		I_STONE,
		I_END
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
		STONE,
		ENTITIES_COUNT
	};
}

namespace Commands {
	enum ID {
		NONE,
		G_EXIT,
		MOVE_FORWARD,
		COMMANDS_COUNT
	};
}
