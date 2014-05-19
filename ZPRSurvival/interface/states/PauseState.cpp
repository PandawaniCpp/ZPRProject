/**
    @date	15.05.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#include "PauseState.h"
#include "../Utility.h"

PauseState::PauseState (StateStack & stack, Context context)
: State (stack, context) {
    stateID = States::PAUSE;
}

void PauseState::draw () {
    context.game->gameWindow->draw (background);
    context.game->gameWindow->draw (text);
}

bool PauseState::update (sf::Time dt) {
    return true;
}

bool PauseState::handleEvent (const Command * command) {
    // "Press any key to continue"	#TODO Implement buttons
    switch (command->commandType) {
        case Commands::G_RESUME: requestStackPop (); break;
        case Commands::G_EXIT: requestStateClear (); context.game->gameWindow->close (); break;
        default: break;
    }

    return true;
}

void PauseState::onActivate () {
    texture.loadFromFile ("resources/textures/pause/background.png");
    background.setTexture (texture);
    background.setScale ((float)GraphicsOptions::videoMode.width / texture.getSize ().x,
                         (float)GraphicsOptions::videoMode.height / texture.getSize ().y);

    text.setFont (context.game->fontHolder.get (Fonts::F_MENU));
    text.setStyle (sf::Text::Bold);
    text.setColor (sf::Color (255, 255, 255, 255));
    text.setCharacterSize (25);
    text.setString ("Press ENTER to continue\n   Press ESCAPE to exit");
    centerOrigin (text);

    context.game->gameWindow->setView (context.game->worldView);
    context.game->worldViewPosition = sf::Vector2f (context.game->worldView.getCenter ().x - context.game->worldView.getSize ().x / 2.f,
                                                    context.game->worldView.getCenter ().y - context.game->worldView.getSize ().y / 2.f);

    background.setPosition (context.game->worldViewPosition);
    text.setPosition ((float)GraphicsOptions::videoMode.width / 2.f + context.game->worldViewPosition.x,
                      (float)GraphicsOptions::videoMode.height / 6.f * 5.f + context.game->worldViewPosition.y);
}

void PauseState::onDestroy () {

}