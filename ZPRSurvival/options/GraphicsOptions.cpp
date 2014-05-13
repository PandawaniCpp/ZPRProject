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
GraphicsOptions::AspectRatio GraphicsOptions::currentAspectRatio = GraphicsOptions::getAspectRatio (&GraphicsOptions::videoMode);

void GraphicsOptions::init () {
	if (!videoMode.isValid ()) {
		videoMode = videoModesAvailable[0];
		currentAspectRatio = getAspectRatio (&videoMode);
	}
}

GraphicsOptions::AspectRatio GraphicsOptions::getAspectRatio (VideoMode * videoMode) {
	float ratio = (float)videoMode->width / (float)videoMode->height;

	if (std::abs(ratio - 4.f / 3.f) < RES_PRECISION)
		return X_4x3;
	else if (std::abs(ratio - 16.f / 9.f) < RES_PRECISION)
		return X_16x9;
	else if (std::abs(ratio - 16.f / 10.f) < RES_PRECISION)
		return X_16x10;
	else
		return X_OTHER;
}

std::string GraphicsOptions::getResolutionsAvailable () {
	std::string resolutions = "";
	std::stringstream ss;

	for (VideoMode & vm : videoModesAvailable) {		// Iterate through all available Video Modes.
		// Conversion unsigned int-> string and concatenation.
		ss << vm.width << " x " << vm.height << " (" << vm.bitsPerPixel << " bits, ";
		
		switch (getAspectRatio(&vm)) {
			case X_4x3: ss << "4x3)\n"; break;
			case X_16x9: ss << "16x9)\n"; break;
			case X_16x10: ss << "16x10)\n"; break;
			default: ss << "other ratio)\n";
		}

		resolutions += ss.str ();
		ss.str ("");
	}

	return resolutions;
}

std::string GraphicsOptions::getCurrentResolution () {
	std::string resolution = "";
	std::stringstream ss;

	// Conversion unsigned int-> string and concatenation.
	ss << videoMode.width << " x " << videoMode.height << " (" << videoMode.bitsPerPixel << " bits, ";
	
	switch (currentAspectRatio) {
		case X_4x3: ss << "4x3)\n"; break;
		case X_16x9: ss << "16x9)\n"; break;
		case X_16x10: ss << "16x10)\n"; break;
		default: ss << "other ratio)\n";
	}

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
