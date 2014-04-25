/**
	@author	Pawel Kaczynski
	@date	23.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <sstream>

using sf::VideoMode;

/**
	Non-instantiable class for specifying graphics options such as fullscreen mode, resolution,
	frame rate, v-sync etc....
*/
class GraphicsOptions {
public:
	// OS's available video modes
	static std::vector<VideoMode> videoModesAvailable;

	// Customizable parameters.
	static bool fullscreenModeOn;		// Toggles fullscreen on/off.
	static bool vSyncOn;				// Vertical synch. on/off.
	static int fps;						// Frames per second rate.
	static VideoMode videoMode;			// Current active Video Mode.
	static VideoMode testVideoMode;		// For testing.
	static int videoStyle;

	// Returns all available resolutions as string. 
	// Each row represents "width x height (depth)"
	static std::string getResolutionsAvailable ();

	// Returns current resolution taken from videoMode.
	// format: "width x height (depth)"
	static std::string getCurrentResolution ();

	// Switch between resolutions.
	static void switchResolution (bool higher);
};

