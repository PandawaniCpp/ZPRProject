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
	stateID = States::GAME;
}

void GameState::draw () {
	context.game->draw();
}

bool GameState::update (sf::Time dt) {
	// Capture and process mouse position
	MouseInterface::capturePosition (*context.game->gameWindow);
	MouseInterface::calculatePlayerOffset (context.game->playerController[0]->getPosition () - context.game->worldViewPosition);
	context.game->playerController[0]->setTargetRotation (MouseInterface::calculateRotation ());		// We know it's player, no need to set up a rotation command.
	context.game->worldView.setCenter (context.game->playerController[0]->getPosition () + MouseInterface::playerOffset);
	context.game->gameWindow->draw (*context.game->playerController[0]);

	context.game->worldViewPosition = sf::Vector2f (context.game->worldView.getCenter ().x - context.game->worldView.getSize ().x / 2.f,
											context.game->worldView.getCenter ().y - context.game->worldView.getSize ().y / 2.f);

	context.game->worldMap->t += rand () % 750 / 100000.0;

	// Calculate player-mouse offset.		#TODO REMOVE?
	//MouseInterface::calculatePlayerOffset (playerController[0]->getPosition () - worldViewPosition);

	//// Pass target rotation to player.
	//float mouseRotation = MouseInterface::calculateRotation ();
	//playerController[0]->setTargetRotation (mouseRotation);		// We know it's player, no need to set up a rotation command.

	// Process to taking commands from CommandQueue
	context.game->commandInterpret ();

	// Update player.
	context.game->playerController.update ();
	context.game->itemController.updateEntities ();

	// Apply physics to b2World
	Player::boxWorld.Step (1.0 / GraphicsOptions::fps, 8, 3);

	// Update console ouput.
	context.game->console->update ("x", context.game->playerController[0]->getPosition ().x);
	context.game->console->update ("y", context.game->playerController[0]->getPosition ().y);
	context.game->console->update ("direction", (float)context.game->playerController[0]->getDirection ());
	context.game->console->update ("rotation", context.game->playerController[0]->getBody ()->GetAngle () * RAD_TO_DEG);
	context.game->console->update ("mouse rotation", MouseInterface::calculateRotation () * RAD_TO_DEG);
	context.game->console->update ("force x", context.game->playerController[0]->getBody ()->GetForce ().x);
	context.game->console->update ("force y", context.game->playerController[0]->getBody ()->GetForce ().y);
	context.game->console->update ("velocity x", context.game->playerController[0]->getBody ()->GetLinearVelocity ().x);
	context.game->console->update ("velocity y", context.game->playerController[0]->getBody ()->GetLinearVelocity ().y);
	context.game->console->update ("b2Body counter", Player::boxWorld.GetBodyCount ());

	// Set the world displacement vector relatively to player.
	//worldView.setCenter (playerController[0]->getPosition () + MouseInterface::playerOffset);
	//worldView.setRotation (45.f);
	context.game->gameWindow->setView (context.game->worldView);

	// Vector for displacement correction.
	sf::Vector2f vec (context.game->worldView.getCenter () - context.game->worldView.getSize () / 2.0f);

	// Correct console displacement (always in top-left corner).
	context.game->console->setPosition (context.game->worldViewPosition);

	// Correct map displacement.
	context.game->worldMap->setPosition (vec);
	//vec.y -= worldMap->getWorldBounds().y - GraphicsOptions::videoMode.height;		// !!!!!
	context.game->worldMap->setViewPosition (vec);
	context.game->worldMap->update ();

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

	switch (event.type) {
		case sf::Event::KeyPressed:
			context.game->commandQueue.push (KeyboardInterface::pressedKeyHandle (context.game->stateStack.getCurrentStateID (), event.key.code));
			break;
		case sf::Event::KeyReleased:
			context.game->commandQueue.push (KeyboardInterface::releasedKeyHandle (context.game->stateStack.getCurrentStateID (), event.key.code));
			break;
		default:break;
	}

	return true;
}

void GameState::onActivate () {
	/*context.game->worldMap = new WorldMapView (time (NULL), 0.65, 5000.0, 8, 5000, 5000);
	context.game->entitiesInit ();
	context.game->layersInit ();
	context.game->objectsInit ();
	context.game->applyOptions ();*/

	context.game->applyOptions ();
}

void GameState::onDestroy () {

}
