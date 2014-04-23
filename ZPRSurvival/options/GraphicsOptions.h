/**
	@author	Pawel Kaczynski
	@date	23.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once

/**
	Non-instantiable class for specifying graphics options such as fullscreen mode, resolution,
	frame rate, v-sync etc....
*/
class GraphicsOptions {
public:
	// Customizable parameters.
	static bool fullscreenModeOn;	// Toggles fullscreen on/off.
	static bool vSyncOn;			// Vertical synch. on/off.
	static bool resizeableWindow;	// Player 
	static int fps;					// Frames per second rate.
};

