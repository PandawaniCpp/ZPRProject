/**
	@date	03.04.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <unordered_map>
#include <sstream>
#include "../classes/GameObject.h"

/** 
	Basically shows transparent layer on top with detailed information about the game.
*/
class Console : public GameObject {
public:
	// If visible.
	static bool visible;

	// Holds all parameters to draw: name - value.
	std::unordered_map<std::string, std::string> params;

	// All available keys. Represent drawing order.
	std::vector<std::string> keys;

	// Default constructor.
	Console ();
	
	// Default destructor.
	virtual ~Console ();

	// Inserts new pair 'name-value' into Console::params.
	void insert (const std::string & name, const float & value);		// + conversion float->string
	void insert (const std::string & name, const std::string & value);

	// Updates existing parameters instead of inserting new ones.
	void update (const std::string & name, const float & value);		// + conversion float->string
	void update (const std::string & name, const std::string & value);

	// Set console's default font from Game::fonts
	void setFont (const sf::Font & font);

	// Set new transparent background accordingly to the current VideoMode size.
	void refresh ();

	// Draw console on the screen with given params.
	// \see Console::params
	virtual void draw (sf::RenderWindow * window) const ;

private:
	sf::Font font;		// Default font to draw with.
	sf::Text text;		// Holds string to show on the screen.
	sf::Color color;	// Font color.
	sf::Texture texture;
	int fontSize;		// Default font size.
	int dy;				// Difference between entries (in pixels)
};

