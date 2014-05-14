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
#include <Box2D/Dynamics/b2World.h>
#include <sstream>
#define RES_PRECISION 0.01f

using sf::VideoMode;

/**
	Non-instantiable class for specifying graphics options such as fullscreen mode, resolution,
	frame rate, v-sync etc....
*/
class GraphicsOptions {
public:
	// Screen aspect ratios
	enum AspectRatio {
		X_4x3,
		X_16x10,
		X_16x9,			
		X_OTHER
	};

	// OS's available video modes
	static std::vector<VideoMode> videoModesAvailable;

	// Customizable graphics parameters.
	static bool fullscreenModeOn;			// Toggles fullscreen on/off.
	static bool vSyncOn;					// Vertical synch. on/off.
	static int fps;							// Frames per second rate.
	static int videoStyle;					// How the window is shown
	static VideoMode videoMode;				// Current active Video Mode.
	static VideoMode baseVideoMode;			// Scaling will be performed accordingly to this VideoMode 
	static VideoMode testVideoMode;			// For testing.
	static AspectRatio currentAspectRatio;	// Current resolution aspect ratio (width x height)

	// Metric definition (for Box2D)
	static float pixelPerMeter;

	// Initialize VideoMode
	static void init ();

	// Returns aspect ratio of given VideoMode
	static AspectRatio getAspectRatio (VideoMode * videoMode);

	// Returns all available resolutions as string. 
	// Each row represents "width x height (depth)"
	static std::string getResolutionsAvailable ();

	// Returns current resolution taken from videoMode.
	// format: "width x height (depth)"
	static std::string getCurrentResolution ();

	// Switch between resolutions.
	static void switchResolution (bool higher);
};

