/**
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
	*/

#include "TitleState.h"

TitleState::TitleState (StateStack & stack, Context context)
: State (stack, context) {
	stateID = States::TITLE;
}

void TitleState::draw () {
	context.game->gameWindow->draw (background);
}

bool TitleState::update (sf::Time dt) {
	return true;
}

bool TitleState::handleEvent (const sf::Event& event) {
	// "Press any key to continue"
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop ();
		requestStackPush (States::MENU);
	}

	return true;
}

void TitleState::onActivate () {
	texture.loadFromFile ("resources/textures/title/background.png");
	background.setTexture (texture);
	background.setPosition (0.f, 0.f);
	background.setScale ((float)GraphicsOptions::videoMode.width / texture.getSize ().x,
						 (float)GraphicsOptions::videoMode.height / texture.getSize ().y);

	context.game->worldView.setCenter ((float)GraphicsOptions::videoMode.width / 2.f, 
									   (float)GraphicsOptions::videoMode.height / 2.f); 
	context.game->gameWindow->setView (context.game->worldView);
	context.game->worldViewPosition = sf::Vector2f (context.game->worldView.getCenter ().x - context.game->worldView.getSize ().x / 2.f,
													context.game->worldView.getCenter ().y - context.game->worldView.getSize ().y / 2.f);
}

void TitleState::onDestroy () {

}