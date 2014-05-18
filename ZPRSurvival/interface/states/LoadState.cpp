/**
@date	15.05.2014

Part of the #TITLE survival game.

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "LoadState.h"

LoadState::LoadState (StateStack & stack, Context context)
: State (stack, context), loadingAnimation (Textures::A_LOADING_ANIM, "resources/textures/load/compass.png", sf::Vector3<int> (100, 100, 6), true, sf::seconds (0.5f)) {
	stateID = States::LOAD;
}

void LoadState::draw () {
	context.game->gameWindow->draw (loadingAnimation);
}

bool LoadState::update (sf::Time dt) {
	loadingAnimation.animate (PlayerController::deltaTime);
	return true;
}

bool LoadState::handleEvent (const sf::Event& event) {
	// "Press any key to continue"	#TODO Implement world loading + sf::Thread
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop ();
		requestStackPush (States::GAME);
	}

	return true;
}

void LoadState::onActivate () {
	context.game->worldView.setCenter ((float)GraphicsOptions::videoMode.width / 2.f,
									   (float)GraphicsOptions::videoMode.height / 2.f);
	context.game->gameWindow->setView (context.game->worldView);
	context.game->worldViewPosition = sf::Vector2f (context.game->worldView.getCenter ().x - context.game->worldView.getSize ().x / 2.f,
													context.game->worldView.getCenter ().y - context.game->worldView.getSize ().y / 2.f);
	
	loadingAnimation.setOrigin (50.f, 50.f);
	loadingAnimation.setPosition (context.game->worldView.getCenter ());
}

void LoadState::onDestroy () {

}