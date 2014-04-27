/**
	@author	Pawel Kaczynski
	@date	23.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "GraphicsOptions.h"

// Static attributes initialization
std::vector<VideoMode> GraphicsOptions::videoModesAvailable = VideoMode::getFullscreenModes ();

bool GraphicsOptions::fullscreenModeOn = false;
bool GraphicsOptions::vSyncOn = true;
int GraphicsOptions::fps = 120;
VideoMode GraphicsOptions::testVideoMode = VideoMode (1280, 720, 32);
VideoMode GraphicsOptions::videoMode = GraphicsOptions::testVideoMode;
int GraphicsOptions::videoStyle = sf::Style::Close | sf::Style::Titlebar;
float GraphicsOptions::pixelPerMeter = 100.0f;
float GraphicsOptions::meterPerPixel = 0.01f;




std::string GraphicsOptions::getResolutionsAvailable () {
	std::string resolutions = "";
	std::stringstream ss;

	for (VideoMode & vm : videoModesAvailable) {		// Iterate through all available Video Modes.
		// Conversion unsigned int-> string and concatenation.
		ss << vm.width << " x " << vm.height << " (" << vm.bitsPerPixel << ")\n";
		resolutions += ss.str ();
		ss.str ("");
	}

	return resolutions;
}

std::string GraphicsOptions::getCurrentResolution () {
	std::string resolution = "";
	std::stringstream ss;

	// Conversion unsigned int-> string and concatenation.
	ss << videoMode.width << " x " << videoMode.height << " (" << videoMode.bitsPerPixel << ")\n";
	resolution += ss.str ();
	ss.str ("");

	return resolution;
}

void GraphicsOptions::switchResolution (bool higher) {
	unsigned int i;			// Searching for current resolution in vector.
	for (i = 0; i < videoModesAvailable.size (); ++i) {
		if (videoModesAvailable[i] == videoMode)
			break;
	}

	int newResIndex;
	if (i == 0 && higher)
		newResIndex = videoModesAvailable.size () - 1;
	else
		higher ? newResIndex = (i - 1) % videoModesAvailable.size () : newResIndex = (i + 1) % videoModesAvailable.size ();
	videoMode = videoModesAvailable[newResIndex];
}
