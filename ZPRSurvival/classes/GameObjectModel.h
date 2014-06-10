/**	
	@date	03.04.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/Graphics.hpp>

/**
	MVC's Model for GameObject class. Base for other Models in whole game.

	\derived: PlayerModel, CreatureModel, ItemModel
*/
class GameObjectModel {
public:
	// Default constructor.
	GameObjectModel ();

	// Default destructor.
	virtual ~GameObjectModel ();

	// Getters

	sf::Vector2<float> getPosition ();
		
	// Setters

	void setPosition (sf::Vector2<float> position);

private:
	sf::Vector2<float> position;		// Object position (in game world).
};