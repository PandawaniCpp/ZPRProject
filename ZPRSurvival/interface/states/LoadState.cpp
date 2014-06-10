/**
    @date	15.05.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "LoadState.h"
#include "../Utility.h"

LoadState::LoadState (StateStack & stack, Game * game)
: State (stack, game),
loadingAnimation (Textures::A_LOADING_ANIM, "resources/textures/load/compass.png",
sf::Vector3<int> (100, 100, 6), true, sf::seconds (0.5f)),
thread (&LoadState::init, this),
loadingTexts ({"Painting the grass", "Spinning the compass", "Frothing the seawater", "Planting moss on northern sides of the trees", "Shredding the sand", "Loading...something...", "Darkening the shadows...", "Inventing the cure for cancer...", "Re-inventing the wheel..."}) {
    stateID = States::LOAD;
}

void LoadState::draw () {
    if (!loadingFinished)
        game->gameWindow->draw (loadingAnimation);
    else
        game->gameWindow->draw (loadingDone);

    game->gameWindow->draw (text);
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

bool LoadState::handleEvent (const Command * command) {
    if (command->commandType == Commands::PRESS_ANY_KEY && loadingFinished) {
        requestStackPop ();
        requestStackPush (States::GAME);
    }

    return true;
}

void LoadState::onActivate () {
    game->worldView.setCenter ((float)GraphicsOptions::videoMode.width / 2.f,
                                       (float)GraphicsOptions::videoMode.height / 2.f);
    game->gameWindow->setView (game->worldView);
    game->worldViewPosition = sf::Vector2f (game->worldView.getCenter ().x - game->worldView.getSize ().x / 2.f,
                                                    game->worldView.getCenter ().y - game->worldView.getSize ().y / 2.f);

    srand ((unsigned)std::time (NULL));

    text.setFont (game->fontHolder.get (Fonts::F_MENU));
    text.setStyle (sf::Text::Bold);
    text.setColor (sf::Color (220, 220, 220, 255));
    text.setCharacterSize (25);
    text.setString (loadingTexts[rand () % loadingTexts.size ()]);
    centerOrigin (text);
    text.setPosition ((float)GraphicsOptions::videoMode.width / 2.f,
                      (float)GraphicsOptions::videoMode.height / 3.f * 2.f);

    loadingAnimation.setOrigin (50.f, 50.f);
    loadingAnimation.setPosition (game->worldView.getCenter ());

    textEffectTime = sf::Time::Zero;

    loadingDoneTexture.loadFromFile ("resources/textures/load/compassDone.png");
    loadingDone.setTexture (loadingDoneTexture);
    centerOrigin (loadingDone);
    loadingDone.setPosition (game->worldView.getCenter ());

    thread.launch ();
}

void LoadState::onDestroy () {

}

void LoadState::init () {
    game->worldMap = new WorldMapView (time (NULL), 0.9, 5000.0, 2, 5000, 5000);
    game->entitiesInit ();
    game->layersInit ();
    game->objectsInit ();
    loadingFinished = true;
}