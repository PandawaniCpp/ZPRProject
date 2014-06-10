/**	
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "GameObjectModel.h"

GameObjectModel::GameObjectModel () {
}

GameObjectModel::~GameObjectModel (){
}

// Getters

sf::Vector2<float> GameObjectModel::getPosition () {
	return position;
}

// Setters

void GameObjectModel::setPosition (sf::Vector2<float> position) {
	this->position = position;
}
