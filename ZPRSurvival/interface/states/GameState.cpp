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
    
    // Insert possible collision connections between entities.
    collisionMatches.insert (std::make_pair (Entities::PLAYER, Entities::PREDATOR));
}

void GameState::draw () {
    context.game->draw ();
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


    // Update player.
    context.game->playerController.update ();
    context.game->itemController.updateEntities ();

    collisionHandle ();

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

    return true;
}

bool GameState::handleEvent (const Command * command) {
    // Combination of special keys pressed at that moment.
    int specialKeys = sf::Keyboard::isKeyPressed (sf::Keyboard::LShift) * KeyboardInterface::SHIFT +
        sf::Keyboard::isKeyPressed (sf::Keyboard::LControl) * KeyboardInterface::CONTROL +
        sf::Keyboard::isKeyPressed (sf::Keyboard::LAlt) * KeyboardInterface::ALT +
        sf::Keyboard::isKeyPressed (sf::Keyboard::LSystem) * KeyboardInterface::SYSTEM;

    // Check every game command
    switch (command->commandType) {
        case Commands::G_PAUSE:
            requestStackPush (States::PAUSE); break;
        case Commands::CON_TRIGGER:
            Console::visible = !Console::visible; break;
        case Commands::RES_UP:
            if (Console::visible && command->specialKeys == specialKeys) {
                GraphicsOptions::switchResolution (true);
                context.game->applyOptions ();
            }
            break;
        case Commands::RES_DOWN:
            if (Console::visible && command->specialKeys == specialKeys) {
                GraphicsOptions::switchResolution (true);
                context.game->applyOptions ();
            }
            break;
        case Commands::SET_FULLSCREEN:
            if (Console::visible && command->specialKeys == specialKeys) {
                if (GraphicsOptions::fullscreenModeOn)
                    context.game->setFullscreenEnabled (false);
                else
                    context.game->setFullscreenEnabled (true);
            }
            break;
        case Commands::SAVE_MAP_TO_IMG:
            if (Console::visible && command->specialKeys == specialKeys)
                context.game->worldMap->getMapImage ().saveToFile ("./resources/zrzut_mapy.png");
            break;
        default: break;
    }

    return true;
}

void GameState::onActivate () {
    GraphicsOptions::optionsInitialized = false;
    context.game->applyOptions ();
}

void GameState::onDestroy () {

}

void GameState::collisionHandle () {
    checkCollisionMatch (Entities::PLAYER, Entities::PREDATOR);
}

bool GameState::checkCollisionMatch (Entities::ID entityA, Entities::ID entityB) {
    auto matchA = collisionMatches.find (std::make_pair (entityA, entityB));
    auto matchB = collisionMatches.find (std::make_pair (entityB, entityA));

    if (matchA != collisionMatches.end () || matchB != collisionMatches.end ())
        return true;
    else
        return false;
}