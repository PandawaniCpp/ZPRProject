/**
	@date	15.05.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
	*/

#include "TitleState.h"
#include "../Utility.h"

TitleState::TitleState (StateStack & stack, Game * game)
	: State (stack, game), textVisible (true), textEffectTime (sf::Time::Zero) {
	stateID = States::TITLE;
}

void TitleState::draw () {
	game->gameWindow->draw (background);
	if (textVisible)
		game->gameWindow->draw (text);
}

bool TitleState::update (sf::Time dt) {
	textEffectTime += dt;

	if (textVisible) {
		if (textEffectTime >= sf::seconds (0.6f)) {
			textVisible = !textVisible;
			textEffectTime = sf::Time::Zero;
		}
	}
	else {
		if (textEffectTime >= sf::seconds (0.3f)) {
			textVisible = !textVisible;
			textEffectTime = sf::Time::Zero;
		}
	}

	return true;
}

bool TitleState::handleEvent (const Command * command) {
	// "Press any key to continue"
	if (command->commandType == Commands::PRESS_ANY_KEY) {
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

	text.setFont (game->fontHolder.get (Fonts::F_MENU));
	text.setStyle (sf::Text::Bold);
	text.setColor (sf::Color (220, 220, 220, 255));
	text.setCharacterSize (16);
	text.setString ("Press any key to continue...");
	centerOrigin (text);
	text.setPosition ((float)GraphicsOptions::videoMode.width / 2.f,
					  (float)GraphicsOptions::videoMode.height / 4.f * 3.f);


	game->worldView.setCenter ((float)GraphicsOptions::videoMode.width / 2.f,
									   (float)GraphicsOptions::videoMode.height / 2.f);
	game->gameWindow->setView (game->worldView);
	game->worldViewPosition = sf::Vector2f (game->worldView.getCenter ().x - game->worldView.getSize ().x / 2.f,
													game->worldView.getCenter ().y - game->worldView.getSize ().y / 2.f);
}

void TitleState::onDestroy () {

}