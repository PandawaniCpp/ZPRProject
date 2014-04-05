/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Console.h"
bool Console::visible = false;

Console::Console () {
	// Set default param to game title and version.
	params.insert (std::make_pair ("#TITLE v. ", 0.345));

	// Set background texture.
	assert (texture.loadFromFile ("resources/console_back.png"));
	texture.setRepeated (true);
	this->setPosition (0, 0);
	this->setScale (sf::Vector2f (20, 20));		// #TODO Set scaling accordingly to window size.
	this->setTexture (texture);

	// Set font specifications.
	color = sf::Color::White;
	fontSize = 12;
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

void Console::setFont (const sf::Font & font) {
	this->font = font;
}

void Console::draw (sf::RenderWindow& window) const {
	if (!visible)
		return;
	
	// Draw background.
	window.draw (*this);
	
	sf::Text tempText = text;
	std::stringstream ss;
	float pos = 5;

	for (auto x : params) {				// Iterate through map and draw everything.
		tempText.setString (x.first);
		tempText.setPosition (5, pos);
		window.draw (tempText);

		ss << x.second;
		tempText.setString (ss.str ());
		tempText.setPosition (100, pos);
		ss.str ("");
		window.draw (tempText);

		pos += dy;
	}
}
