/**
    @date	15.05.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "MenuState.h"
#include "../Utility.h"

MenuState::MenuState (StateStack & stack, Game * game)
: State (stack, game) {
    stateID = States::MENU;
}

void MenuState::draw () {
    game->gameWindow->draw (background);
    game->gameWindow->draw (text);
}

bool MenuState::update (sf::Time dt) {
    return true;
}

bool MenuState::handleEvent (const Command * command) {
    // "Press any key to continue"      
    if (command->commandType == Commands::PRESS_ANY_KEY) {
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

    text.setFont (game->fontHolder.get (Fonts::F_MENU));
    text.setStyle (sf::Text::Bold);
    text.setColor (sf::Color (200, 200, 200, 255));
    text.setCharacterSize (25);
    text.setString ("MENU\nPress any key to continue...");
    centerOrigin (text);
    text.setPosition ((float)GraphicsOptions::videoMode.width / 2.f,
                      (float)GraphicsOptions::videoMode.height / 6.f * 5.f);

    game->worldView.setCenter ((float)GraphicsOptions::videoMode.width / 2.f,
                                       (float)GraphicsOptions::videoMode.height / 2.f);
    game->gameWindow->setView (game->worldView);
    game->worldViewPosition = sf::Vector2f (game->worldView.getCenter ().x - game->worldView.getSize ().x / 2.f,
                                                    game->worldView.getCenter ().y - game->worldView.getSize ().y / 2.f);
}

void MenuState::onDestroy () {

}