/**
    @date	03.04.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Game.h"
#include "states/GameState.h"
#include "states/TitleState.h"
#include "states/MenuState.h"
#include "states/LoadState.h"
#include "states/PauseState.h"

// #TITLE
std::string Game::TITLE = "#TITLE";

Game::Game ()
: stateStack (new StateStack (this)) {

    // All we need to play.
    GraphicsOptions::init ();
    gameWindow = new sf::RenderWindow (GraphicsOptions::videoMode, Game::TITLE, GraphicsOptions::videoStyle);	// Create new Window
    console = new Console ();
}

Game::~Game () {
    delete gameWindow;
    delete stateStack;

    // Scene graph's destructor deallocates all graph's objects (all views).
    // #TODO CHECK THIS
}

void Game::initialize () {
    // sf::View init.
    worldView = gameWindow->getDefaultView ();

    gameWindow->setKeyRepeatEnabled (false);			// Prevents from unintended key repetition

    // Initialize factory with prefabs and keyboard interface with key mappings.
    EntityFactory::prefabInit ();
    KeyboardInterface::assignKeys ();
    KeyboardInterface::assignActions ();

    // Set fonts
    fontHolder.load (Fonts::F_MENU, "resources/segoeuil.ttf");
    fontHolder.load (Fonts::F_CONSOLE, "resources/droidmono.ttf");

    // World information 
    // #TODO Delete this crap?
    worldBounds.top = worldBounds.left = 0.f;	// Top left corner (0, 0)
    worldBounds.height = 10000;					// World size
    worldBounds.width = 10000;					// #TODO put proper numbers from WorldMap

    // Create states hierarchy and initialize first state.
    registerStates ();
    stateStack->pushState (States::TITLE);  // Initialize first state.
    stateStack->applyPendingChanges ();
}

void Game::run () {
    // Calculates time difference between frames and corrects occasional lags (if occured).
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    timePerFrame = sf::seconds (1.f / GraphicsOptions::fps);			// Static frame, (1 / x) = x fps.
    timeSinceLastUpdate += clock.restart ();
    PlayerController::deltaTime = timePerFrame;
    ItemController::deltaTime = timePerFrame;
    CreatureController::deltaTime = timePerFrame;

    // Main game loop (handle events -> update everything -> render eveything)
    while (gameWindow->isOpen ()) {
        processEvents ();
        timeSinceLastUpdate += clock.restart ();			// This whole idea is to protect...

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            processEvents ();

            //if (gameWindow->isOpen ())      // If still open
                update ();
                                                            //...game from lags' consequences. 
        }
        render ();

        // Calculate and show the fps value of the previous frame
        currentFPS = 1000.f / (float)clock.getElapsedTime ().asMilliseconds ();
        console->update ("fps", currentFPS);
        console->draw (gameWindow);
    }
}

void Game::terminate () {

}

void Game::registerStates () {
    stateStack->registerState<GameState> (States::GAME);
    stateStack->registerState<TitleState> (States::TITLE);
    stateStack->registerState<MenuState> (States::MENU);
    stateStack->registerState<LoadState> (States::LOAD);
    stateStack->registerState<PauseState> (States::PAUSE);
    /*stateStack->registerState<SettingsState> (States::Settings);
    stateStack->registerState<GameOverState> (States::GameOver, "Mission Failed!");
    stateStack->registerState<GameOverState> (States::MissionSuccess, "Mission Successful!");*/
}

void Game::entitiesInit () {
    playerController.createEntity (Entities::PLAYER, Textures::P_IDLE, sf::Vector2f (5000.f, 5000.f), sf::Vector2i (50, 50));		// #SETSPAWN
    itemController.createEntity (Entities::WALL, Textures::I_WALL, sf::Vector2f (4500.f, 5000.f), sf::Vector2i (450, 300));
    creatureController.createEntity (Entities::ZOMBIE, Textures::C_ZOMBIE, sf::Vector2f (4500.f, 4800.f), sf::Vector2i (150, 150));
}

void Game::layersInit () {
    // Initialize game scene graph
    for (std::size_t i = 0; i < LAYER_COUNT; ++i) {
        GameObject::ObjectPtr layer (new GameObject ());
        sceneLayers[i] = layer.get ();
        sceneGraph.attachChild (layer);
    }

    // Attach map, console and player to game layers
    sceneLayers[Game::CONSOLE]->attachChild (GameObject::ObjectPtr (console));
    sceneLayers[Game::MAP]->attachChild (GameObject::ObjectPtr (worldMap));
    sceneLayers[Game::PLAYER]->attachChild (GameObject::ObjectPtr (playerController[0]));
    sceneLayers[Game::ITEMS]->attachChild (GameObject::ObjectPtr (itemController[0]));
    sceneLayers[Game::CREATURES]->attachChild (GameObject::ObjectPtr (creatureController[0]));

}

void Game::objectsInit () {
    // Set default console's parameters
    console->insert ("x", 0);
    console->insert ("y", 0);
    console->insert ("direction", 0);
    console->insert ("rotation", 0);
    console->insert ("current resolution", GraphicsOptions::getCurrentResolution ());
    console->insert ("b2Body counter", 0);
    console->insert ("avail. resolutions", GraphicsOptions::getResolutionsAvailable ());
    console->setFont (fontHolder.get (Fonts::F_CONSOLE));
}

void Game::applyOptions () {
    GraphicsOptions::vSyncOn ? gameWindow->setVerticalSyncEnabled (true) : gameWindow->setVerticalSyncEnabled (false);

    if (GraphicsOptions::optionsInitialized)
        gameWindow->create (GraphicsOptions::videoMode, Game::TITLE, GraphicsOptions::videoStyle);
    console->update ("current resolution", GraphicsOptions::getCurrentResolution ());

    // Set scaling for new resolution ratio
    //

    // #TODO Do we need this?
    // If needed, set black stripes at the top and bottom of the screen
    //

    // Update sf::View
    worldView = gameWindow->getDefaultView ();
    worldView.setCenter (playerController[0]->getPosition ());
    gameWindow->setView (worldView);
    worldViewPosition = sf::Vector2f (worldView.getCenter ().x - worldView.getSize ().x / 2.f,
                                      worldView.getCenter ().y - worldView.getSize ().y / 2.f);

    if (!GraphicsOptions::optionsInitialized)
        GraphicsOptions::optionsInitialized = true;
}

void Game::processEvents () {
    // Handle keyboard input.
    sf::Event event;

    // State ID of the top state on the stack.
    States::ID currentState = stateStack->getCurrentStateID ();

    // Catch event.
    while (gameWindow->pollEvent (event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                if (currentState & (States::TITLE | States::MENU | States::LOAD))      // "Press any key to continue"
                    event.key.code = sf::Keyboard::Return;
                commandQueue.push (KeyboardInterface::pressedKeyHandle (currentState, event.key.code));
                break;
            case sf::Event::KeyReleased:
                commandQueue.push (KeyboardInterface::releasedKeyHandle (currentState, event.key.code));
                break;
            default:break;
        }

        // Execute all pending commands on proper state.
        commandInterpret ();

        if (event.type == sf::Event::Closed)
            gameWindow->close ();
    }
}

void Game::commandInterpret () {
    while (!commandQueue.isEmpty ()) {
        Command * command = commandQueue.pop ();
        if (command->commandType == Commands::NONE) {
            delete command;     
            continue;
        }
        if (command->category == Entities::NONE) {
            stateStack->handleEvent (command);
        }
        else {
            sceneGraph.passCommand (command, PlayerController::deltaTime);
        }
    }
}

void Game::gameCommandExecute (Command * command) {
   // #TODO REMOVE !!!
}

void Game::update () {
    stateStack->update (PlayerController::deltaTime);	
}

void Game::render () {
    gameWindow->clear ();		// Clear eveything.
    stateStack->draw ();
    gameWindow->display ();
}

void Game::draw () {
    // Draw all layers in order.
    sceneGraph.drawAll (gameWindow);
}

void Game::attachChild (GameObject::ObjectPtr * shPtr, Game::Layer layer) {
    GameObject::ObjectPtr ptrLayer (*shPtr);
    sceneLayers[layer]->attachChild (ptrLayer);
}

void Game::setFullscreenEnabled (bool enable) {
    if (enable) {
        gameWindow->create (GraphicsOptions::videoMode, "ZPR Survival", sf::Style::Fullscreen);
        GraphicsOptions::videoStyle = sf::Style::Fullscreen;
    }
    else {
        gameWindow->create (GraphicsOptions::videoMode, "ZPR Survival", sf::Style::Close | sf::Style::Titlebar);
        GraphicsOptions::videoStyle = sf::Style::Close | sf::Style::Titlebar;
    }

    GraphicsOptions::fullscreenModeOn = !GraphicsOptions::fullscreenModeOn;
}