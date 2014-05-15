/**
	@author	Pawel Kaczynski
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
	*/

#include "GameState.h"

GameState::GameState (StateStack & stack, Context context)
: State (stack, context) {
	this->game = context.game;
}

void GameState::draw () {
	game->draw();
}

bool GameState::update (sf::Time dt) {
	game->worldViewPosition = sf::Vector2f (game->worldView.getCenter ().x - game->worldView.getSize ().x / 2.f,
											game->worldView.getCenter ().y - game->worldView.getSize ().y / 2.f);

	game->worldMap->t += rand () % 750 / 100000.0;

	// Calculate player-mouse offset.		#TODO REMOVE?
	//MouseInterface::calculatePlayerOffset (playerController[0]->getPosition () - worldViewPosition);

	//// Pass target rotation to player.
	//float mouseRotation = MouseInterface::calculateRotation ();
	//playerController[0]->setTargetRotation (mouseRotation);		// We know it's player, no need to set up a rotation command.

	// Process to taking commands from CommandQueue
	game->commandInterpret ();

	// Update player.
	game->playerController.update ();
	game->itemController.updateEntities ();

	// Apply physics to b2World
	Player::boxWorld.Step (1.0 / GraphicsOptions::fps, 8, 3);

	// Update console ouput.
	game->console->update ("x", game->playerController[0]->getPosition ().x);
	game->console->update ("y", game->playerController[0]->getPosition ().y);
	game->console->update ("direction", (float)game->playerController[0]->getDirection ());
	game->console->update ("rotation", game->playerController[0]->getBody ()->GetAngle () * RAD_TO_DEG);
	game->console->update ("mouse rotation", MouseInterface::calculateRotation () * RAD_TO_DEG);
	game->console->update ("force x", game->playerController[0]->getBody ()->GetForce ().x);
	game->console->update ("force y", game->playerController[0]->getBody ()->GetForce ().y);
	game->console->update ("velocity x", game->playerController[0]->getBody ()->GetLinearVelocity ().x);
	game->console->update ("velocity y", game->playerController[0]->getBody ()->GetLinearVelocity ().y);
	game->console->update ("b2Body counter", Player::boxWorld.GetBodyCount ());

	// Set the world displacement vector relatively to player.
	//worldView.setCenter (playerController[0]->getPosition () + MouseInterface::playerOffset);
	//worldView.setRotation (45.f);
	game->gameWindow->setView (game->worldView);

	// Vector for displacement correction.
	sf::Vector2f vec (game->worldView.getCenter () - game->worldView.getSize () / 2.0f);

	// Correct console displacement (always in top-left corner).
	game->console->setPosition (game->worldViewPosition);

	// Correct map displacement.
	game->worldMap->setPosition (vec);
	//vec.y -= worldMap->getWorldBounds().y - GraphicsOptions::videoMode.height;		// !!!!!
	game->worldMap->setViewPosition (vec);
	game->worldMap->update ();

	/*if (!mWorld.hasAlivePlayer ()) {
		mPlayer.setMissionStatus (Player::MissionFailure);
		requestStackPush (States::GameOver);
		}
		else if (mWorld.hasPlayerReachedEnd ()) {
		mPlayer.setMissionStatus (Player::MissionSuccess);
		requestStackPush (States::MissionSuccess);
		}*/

	/*CommandQueue & commands = mWorld.getCommandQueue ();
	mPlayer.handleRealtimeInput (commands);*/

	return true;
}

bool GameState::handleEvent (const sf::Event& event) {
	//// Game input handling
	//CommandQueue& commands = mWorld.getCommandQueue ();
	//mPlayer.handleEvent (event, commands);

	//// Escape pressed, trigger the pause screen
	//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	//	requestStackPush (States::Pause);

	return true;
}

void GameState::onActivate () {
	game->entitiesInit ();
	game->layersInit ();
	game->objectsInit ();
	game->applyOptions ();
}

void GameState::onDestroy () {

}
