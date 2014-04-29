/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "SurvivalObjectController.h"
sf::Time SurvivalObjectController::deltaTime = sf::Time::Zero;

SurvivalObjectController::SurvivalObjectController () {
}

SurvivalObjectController::~SurvivalObjectController () {
}

void SurvivalObjectController::insertAnimationData (Textures::ID textureID, sf::Vector3<int> frameData) {
	SurvivalObjectView::frameData.insert (std::make_pair (textureID, frameData));
}
