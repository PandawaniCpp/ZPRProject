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
	game->render ();
}

bool GameState::update (sf::Time dt) {
	game->update ();

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
