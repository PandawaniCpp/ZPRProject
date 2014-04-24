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
	text.setCharacterSize (fontSize);			
	text.setColor (color);
	text.setPosition (5, 5);
	dy = fontSize + 5;

	// Set available keys.
	keys.push_back ("#TITLE v.");
	keys.push_back ("x");
	keys.push_back ("y");
	keys.push_back ("dx");
	keys.push_back ("dy");
	keys.push_back ("direction");
	keys.push_back ("rotation");
	keys.push_back ("current resolution");
	keys.push_back ("avail. resolutions");		// <- Should be the last one

	// Set default param to game title and version.
	this->insert ("#TITLE v.", "0.5.1");
}

Console::~Console () {

}

void Console::insert (const std::string & name, const float & value) {
	for (auto & x : keys) {
		if (name == x) {
			std::stringstream ss;
			ss << value;
			auto inserted = params.insert (std::make_pair (name, ss.str ()));
			assert (inserted.second);
			break;
		}
	}
}

void Console::insert (const std::string & name, const std::string & value) {
	for (auto & x : keys) {
		if (name == x) {
			auto inserted = params.insert (std::make_pair (name, value));
			assert (inserted.second);
			break;
		}
	}
}

void Console::update (const std::string & name, const float & value) {
	auto found = params.find (name);		//find resource by id
	assert (found != params.end ());		//break if given resource doesn't exist
	std::stringstream ss;
	ss << value;
	found->second = ss.str();
}

void Console::update (const std::string & name, const std::string & value) {
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

	for (auto & x : keys) {				// Iterate through set of available keys.
		std::unordered_map<std::string, std::string>::const_iterator it;
		it = params.find (x);
		if (it == params.end ())
			continue;

		tempText.setString (it->first);
		tempText.setPosition (5, pos);
		window.draw (tempText);

		ss << it->second;
		tempText.setString (ss.str ());
		tempText.setPosition (150, pos);	// #TODO Set scaling to window accordingly
		ss.str ("");
		window.draw (tempText);

		pos += dy;
	}
}
