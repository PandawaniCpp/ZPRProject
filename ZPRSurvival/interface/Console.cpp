/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Console.h"

Console::Console () {
	// Set default param to game title and version.
	params.insert (std::make_pair ("#TITLE", 0.245));

	// Set font specification.
	font.loadFromFile ("resources/segoeuil.ttf");
	color.r = 200;
	color.g = 200;
	color.b = 200;
	fontSize = 20;
	text.setFont (font);
	text.setCharacterSize (fontSize);			// #TODO make private variables for color, font and size
	text.setColor (color);
	text.setString (params.begin()->first);
	text.setPosition (5, 5);
	dy = fontSize + 5;
}

Console::~Console () {
}

void Console::insert (const std::string & name, const float & value) {
	auto inserted = params.insert (std::make_pair (name, value));
	assert (inserted.second);
}

void Console::update (const std::string & name, const float & value) {
	auto found = params.find (name);		//find resource by id
	assert (found != params.end ());		//break if given resource doesn't exist
	found->second = value;
}

void Console::draw (sf::RenderWindow& window) const {
	sf::Text tempText = text;
	int pos = 5;

	for (auto x : params) {				// Iterate through map and draw everything.
		tempText.setString (x.first);
		tempText.setPosition (5, pos);
		pos += dy;
		window.draw (tempText);
	}
}
