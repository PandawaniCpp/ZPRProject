/**
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "MenuState.h"
#include "../Utility.h"

MenuState::MenuState (StateStack & stack, Context context)
: State (stack, context) {
	stateID = States::MENU;
}

void MenuState::draw () {
	context.game->gameWindow->draw (background);
	context.game->gameWindow->draw (text);
}

bool MenuState::update (sf::Time dt) {
	return true;
}

bool MenuState::handleEvent (const sf::Event& event) {
	// "Press any key to continue"	#TODO Implement buttons
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop ();
		requestStackPush (States::LOAD);
	}

	return true;
}

void MenuState::onActivate () {
	texture.loadFromFile ("resources/textures/menu/background.png");
	background.setTexture (texture);
	background.setPosition (0.f, 0.f);
	background.setScale ((float)GraphicsOptions::videoMode.width / texture.getSize ().x,
						 (float)GraphicsOptions::videoMode.height / texture.getSize ().y);

	text.setFont (context.game->fontHolder.get (Fonts::F_MENU));
	text.setStyle (sf::Text::Bold);
	text.setColor (sf::Color (50, 50, 50, 255));
	text.setCharacterSize (25);
	text.setString ("MENU\nPress any key to continue...");
	centerOrigin (text);
	text.setPosition ((float)GraphicsOptions::videoMode.width / 2.f,
					  (float)GraphicsOptions::videoMode.height / 6.f * 5.f);

	context.game->worldView.setCenter ((float)GraphicsOptions::videoMode.width / 2.f,
									   (float)GraphicsOptions::videoMode.height / 2.f);
	context.game->gameWindow->setView (context.game->worldView);
	context.game->worldViewPosition = sf::Vector2f (context.game->worldView.getCenter ().x - context.game->worldView.getSize ().x / 2.f,
													context.game->worldView.getCenter ().y - context.game->worldView.getSize ().y / 2.f);
}

void MenuState::onDestroy () {

}