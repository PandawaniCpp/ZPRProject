/**
@date	15.05.2014

Part of the #TITLE survival game.

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "LoadState.h"
#include "../Utility.h"

LoadState::LoadState (StateStack & stack, Context context)
	: State (stack, context),
	loadingAnimation (Textures::A_LOADING_ANIM, "resources/textures/load/compass.png",
	sf::Vector3<int> (100, 100, 6), true, sf::seconds (0.5f)),
	thread (&LoadState::init, this),
	loadingTexts ({"Painting the grass", "Spinning the compass", "Frothing the seawater", "Planting moss on northern sides of the trees", "Shredding the sand"}) {
	stateID = States::LOAD;
}

void LoadState::draw () {
	if (!loadingFinished)
		context.game->gameWindow->draw (loadingAnimation);
	else
		context.game->gameWindow->draw (loadingDone);

	context.game->gameWindow->draw (text);
}

bool LoadState::update (sf::Time dt) {
	if (!loadingFinished)
		loadingAnimation.animate (PlayerController::deltaTime);

	textEffectTime += dt;

	if (loadingFinished) {
		text.setString ("Game loaded, press any key to continue...");
		centerOrigin (text);
		text.setPosition ((float)GraphicsOptions::videoMode.width / 2.f,
						  (float)GraphicsOptions::videoMode.height / 3.f * 2.f);
	}
	else if (textEffectTime >= sf::seconds (2.f)) {
		text.setString (loadingTexts[rand () % loadingTexts.size ()]);
		centerOrigin (text);
		text.setPosition ((float)GraphicsOptions::videoMode.width / 2.f,
						  (float)GraphicsOptions::videoMode.height / 3.f * 2.f);
		textEffectTime = sf::Time::Zero;
	}

	return true;
}

bool LoadState::handleEvent (const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && loadingFinished) {
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

	srand ((unsigned)std::time (NULL));

	text.setFont (context.game->fontHolder.get (Fonts::F_MENU));
	text.setStyle (sf::Text::Bold);
	text.setColor (sf::Color (220, 220, 220, 255));
	text.setCharacterSize (25);
	text.setString (loadingTexts[rand () % loadingTexts.size ()]);
	centerOrigin (text);
	text.setPosition ((float)GraphicsOptions::videoMode.width / 2.f,
					  (float)GraphicsOptions::videoMode.height / 3.f * 2.f);

	loadingAnimation.setOrigin (50.f, 50.f);
	loadingAnimation.setPosition (context.game->worldView.getCenter ());

	textEffectTime = sf::Time::Zero;

	loadingDoneTexture.loadFromFile ("resources/textures/load/compassDone.png");
	loadingDone.setTexture (loadingDoneTexture);
	centerOrigin (loadingDone);
	loadingDone.setPosition (context.game->worldView.getCenter ());

	thread.launch ();
}

void LoadState::onDestroy () {

}

void LoadState::init () {
	context.game->worldMap = new WorldMapView (time (NULL), 0.65, 5000.0, 8, 5000, 5000);
	context.game->entitiesInit ();
	context.game->layersInit ();
	context.game->objectsInit ();
	loadingFinished = true;
}