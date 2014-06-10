/**
    @date	15.05.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#include "GameState.h"

GameState::GameState (StateStack & stack, Game * game)
: State (stack, game) {
    stateID = States::GAME;
    
    // Insert possible collision connections between entities.
    collisionMatches.insert (std::make_pair (Entities::PLAYER, Entities::ZOMBIE));
}

void GameState::draw () {
    game->draw ();
}

bool GameState::update (sf::Time dt) {
    // Capture and process mouse position
    MouseInterface::capturePosition (*game->gameWindow);
    MouseInterface::calculatePlayerOffset (game->playerController[0]->getPosition () - game->worldViewPosition);
    game->playerController[0]->setTargetRotation (MouseInterface::calculateRotation ());		// We know it's player, no need to set up a rotation command.
    game->worldView.setCenter (game->playerController[0]->getPosition () + MouseInterface::playerOffset);
    game->gameWindow->draw (*game->playerController[0]);

    game->worldViewPosition = sf::Vector2f (game->worldView.getCenter ().x - game->worldView.getSize ().x / 2.f,
                                                    game->worldView.getCenter ().y - game->worldView.getSize ().y / 2.f);

    game->worldMap->t += rand () % 750 / 100000.0;

    // Update player.
    game->playerController.update ();
    game->itemController.updateEntities ();
    game->creatureController.update (game->playerController[0]->getPosition());

    // Check every contact and interpret it.
    collisionHandle ();

    // Apply physics to b2World
    Player::boxWorld.Step (1.0 / GraphicsOptions::fps, 8, 3);

    // Remove scheduled entities.
    //applyPendingEntitiesRemoval ();

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
                game->applyOptions ();
            }
            break;
        case Commands::RES_DOWN:
            if (Console::visible && command->specialKeys == specialKeys) {
                GraphicsOptions::switchResolution (true);
                game->applyOptions ();
            }
            break;
        case Commands::SET_FULLSCREEN:
            if (Console::visible && command->specialKeys == specialKeys) {
                if (GraphicsOptions::fullscreenModeOn)
                    game->setFullscreenEnabled (false);
                else
                    game->setFullscreenEnabled (true);
            }
            break;
        case Commands::SAVE_MAP_TO_IMG:
            if (Console::visible && command->specialKeys == specialKeys)
                game->worldMap->getMapImage ().saveToFile ("./resources/zrzut_mapy.png");
            break;
        case Commands::START_SIMULATION:
            game->creatureController.createEntity (Entities::ZOMBIE, Textures::C_ZOMBIE, game->playerController[0]->getPosition() + sf::Vector2f(300,300), sf::Vector2i (150, 150));
            game->sceneLayers[Game::CREATURES]->attachChild (GameObject::ObjectPtr (game->creatureController[game->creatureController.getSize() -1]));
            game->creatureController.start ();
            break;

        default: break;
    }

    return true;
}

void GameState::onActivate () {
    GraphicsOptions::optionsInitialized = false;
    game->applyOptions ();
}

void GameState::onDestroy () {

}

void GameState::collisionHandle () {
    b2Contact * contact;
    contact = GameObject::boxWorld.GetContactList ();
    while (contact) {
        if (contact->IsTouching ()) {
            b2Body * bA = contact->GetFixtureA ()->GetBody ();
            b2Body * bB = contact->GetFixtureB ()->GetBody ();
            GameObject::EntityInfo * infoA = static_cast<GameObject::EntityInfo*>(bA->GetUserData ());
            GameObject::EntityInfo * infoB = static_cast<GameObject::EntityInfo*>(bB->GetUserData ());
            if (checkCollisionMatch (infoA->type, infoB->type)) {
                // #TEMP
                contact = contact->GetNext ();
                if (infoA->type == Entities::ZOMBIE || infoB->type == Entities::ZOMBIE) {
                    entitiesScheduledForRemoval.insert (infoA->type == Entities::ZOMBIE ? bA : bB);
                }
                continue;
            }
        }
        contact = contact->GetNext ();
    }
}

bool GameState::checkCollisionMatch (Entities::ID entityA, Entities::ID entityB) {
    auto matchA = collisionMatches.find (std::make_pair (entityA, entityB));
    auto matchB = collisionMatches.find (std::make_pair (entityB, entityA));

    if (matchA != collisionMatches.end () || matchB != collisionMatches.end ())
        return true;
    else
        return false;
}

void GameState::applyPendingEntitiesRemoval () {
    for (auto & entity : entitiesScheduledForRemoval) {
        GameObject::EntityInfo * info = static_cast<GameObject::EntityInfo*>(entity->GetUserData ());
        game->sceneGraph.detachById (info->id);
        GameObject::boxWorld.DestroyBody (entity);
        game->creatureController.deleteById (info->id);
    }
}