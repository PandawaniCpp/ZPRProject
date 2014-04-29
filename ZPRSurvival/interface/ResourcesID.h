/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once

// List of all textures in the game.
namespace Textures {
	enum ID {
		P_INIT = 0,
		P_IDLE,		//P_xxx - player textures
		P_WALK,
		P_END,
		I_STONE, // = 100	//I_xxx - item textures
		//C_xxx - creature textures
		//M_xxx - map elements textures
		TEXTURE_COUNT
	};
}

// List of all differen font used in the game.
namespace Fonts {
	enum ID {
		F_MENU,
		F_CONSOLE,
		FONT_COUNT
	};
}