#include "Game.h"

Game::Game() {
	//all we need to play
	gameWindow = new RenderWindow(VideoMode(1200, 700), "ZPR Survival");
	keyboard = new KeyboardInterface();
	mouse = new MouseInterface();
	playerController = new PlayerController();
	state = Game::State::INIT;
	TIME_PER_FRAME = seconds(1.f / 100.f);		//static frame (60 fps)

	generator = new MapGenerator(100, 100, 100);		//#TEMP
	//mapTexture.loadFromImage(generator->GetMap());  
	//mapSprite.setTexture(mapTexture);
	//mapSprite.setPosition (-1024+600, -1024+350);			
	generator->GetMap().saveToFile("Map.png");

	worldBounds.top = worldBounds.left = 0.f;	//top left corner (0, 0)
	worldBounds.height = 0;			//world size
	worldBounds.width = 0;			// #TODO put proper numbers
	worldView = gameWindow->getDefaultView ();
	font.loadFromFile("resources/segoeuil.ttf");
}

Game::~Game() {
	delete gameWindow;
	delete playerController;
	delete keyboard;
	delete mouse;
	delete generator;
}

void Game::initialize() {
	//GameState::State::INIT
	gameWindow->setKeyRepeatEnabled (false);
	gameWindow->setPosition(Vector2<int>(0, 0));		//push the gameWindow to the AnimatedState::LEFT-top corner
	this->state = Game::State::IN_MENU;

		//GameState::State::IN_MENU
	//empty (for now)

		//GameState::State::PLAYING
	//#TEMP later these calls will be in other methods

	playerController->setPlayer();	//prepares player for the game		#TODO maybe put this in constructor
		//set player position to the center of the screen
	playerController->getPlayer()->setPosition(Vector2<float>((float)gameWindow->getSize().x / 2, (float)gameWindow->getSize().y / 2));
}

void Game::run() {
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	timeSinceLastUpdate += clock.restart ();

	while (gameWindow->isOpen()) {
		processEvents();
		timeSinceLastUpdate += clock.restart ();			//this whole idea is to prevent...

		while (timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents();

			if (state == Game::State::EXIT)
				gameWindow->close();

			update(TIME_PER_FRAME);						//...game from occasional lags
		}
		render();
	}
}

void Game::terminate() {

}

void Game::processEvents() {
		//handle mouse position and imput
	mouse->capturePosition(*gameWindow);

		//handle keyboard input
	Event event;
	int newState = -1;
	while (gameWindow->pollEvent(event)) {
		switch (event.type) {
		case Event::KeyPressed:			//inputHandle() returns proper new state
			newState = keyboard->inputHandle(event.key.code, true, state, playerController);
			break;
		case Event::KeyReleased:
			newState = keyboard->inputHandle(event.key.code, false, state, playerController);
			break;
		case Event::Closed:
			gameWindow->close();
			break;
		default:
			break;
		}
	}

	switch (newState) {
		case Game::State::UNKNOWN: state = Game::State::UNKNOWN; break;
		case Game::State::INIT: state = Game::State::INIT; break;
		case Game::State::IN_MENU: state = Game::State::IN_MENU; break;
		case Game::State::PLAYING: state = Game::State::PLAYING; break;
		case Game::State::PAUSE: state = Game::State::PAUSE; break;
		case Game::State::EXIT: state = Game::State::EXIT; break;
		default:
			break;
	}
}

void Game::update(Time deltaTime) {
	playerController->setDeltaTime(deltaTime);
	playerController->update (mouse->getPosition ());

	//set the world displacement vector relatively to player
	globalDisplacement = playerController->getPlayer()->getDisplacement();
	generator->move(-globalDisplacement);
	// ^ mind the sign!
}

void Game::render() {
	gameWindow->clear();
	playerController->render ();
	this->draw();

	//#TEMP test
	stringstream ss;
	ss << playerController->getPlayer()->getDisplacement().x;
	std::string result(ss.str());
	Text text(result, font);
	text.setCharacterSize(30);
	text.setColor(Color::White);
	text.setPosition(10, 5);
	gameWindow->draw(text);

	ss.str("");
	ss << playerController->getPlayer ()->getDisplacement().y;
	result = ss.str();
	text.setString(result);
	text.setPosition(10, 30);
	gameWindow->draw(text);

	ss.str("");
	ss << generator->getPosition().x;
	result = ss.str();
	text.setString(result);
	text.setPosition(10, 55);
	gameWindow->draw(text);

	ss.str("");
	ss << generator->getPosition().y;
	result = ss.str();
	text.setString(result);
	text.setPosition(10, 80);
	gameWindow->draw(text);

	ss.str ("");
	ss << playerController->getPlayer()->getDirection ();
	result = ss.str ();
	text.setString (result);
	text.setPosition (10, 105);
	gameWindow->draw (text);
	//=================================

	gameWindow->display();
}

void Game::draw() {
	//gameWindow->draw(mapSprite);
	generator->draw(gameWindow);
	playerController->getPlayerView()->draw(*gameWindow);
}

