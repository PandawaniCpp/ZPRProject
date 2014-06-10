#include "WorldMapView.h"


WorldMapView::WorldMapView() {
	mapa = new WorldMap();
	t = 0.0f;
	// = new sf::RenderTexture();
	initialize();
}

WorldMapView::WorldMapView(int seed, double persistence, double zoom, int octaves, int width, int height) {
	mapa = new WorldMap(seed, persistence, zoom, octaves, width, height);
	t = 0.0f;
	initialize();
}

void WorldMapView::initialize() {
	Logger::getInstance() << "poczatek";
	Logger::getInstance() << std::endl;
	int width = mapa->getWidth();
	int height = mapa->getHeight();
	Logger::getInstance() << "start saving";
	Logger::getInstance() << std::endl;
	//getMapImage().saveToFile("./takamapa.png");
	Logger::getInstance() << "end saving";
	Logger::getInstance() << std::endl;
	waterImage = new sf::Image();
	sandImage = new sf::Image();
	grassImage = new sf::Image();
	waterTexture = new sf::Texture();
	sandTexture = new sf::Texture();
	grassTexture = new sf::Texture();
	waterImage->create(static_cast<float>(GraphicsOptions::videoMode.width), static_cast<float>(GraphicsOptions::videoMode.height), sf::Color::Blue);
	sandImage->create(static_cast<float>(GraphicsOptions::videoMode.width), static_cast<float>(GraphicsOptions::videoMode.height), sf::Color::Yellow);
	grassImage->create(static_cast<float>(GraphicsOptions::videoMode.width), static_cast<float>(GraphicsOptions::videoMode.height), sf::Color::Green);
	//image->loadFromFile("./resources/textures/background/grassx.png");
	grassImage->loadFromFile("./resources/textures/background/grassx.png");
	sandImage->loadFromFile("./resources/textures/background/piachx.png");
	waterTexture->loadFromImage(*waterImage);
	sandTexture->loadFromImage(*sandImage);
	grassTexture->loadFromImage(*grassImage);
	waterTexture->setRepeated(true);
	sandTexture->setRepeated(true);
	grassTexture->setRepeated(true);
	waterSprite = new Sprite(*waterTexture, sf::IntRect(0, 0, width, height));
	sandSprite = new Sprite(*sandTexture, sf::IntRect(0, 0, width, height));
	grassSprite = new Sprite(*grassTexture, sf::IntRect(0, 0, width, height));
	poisson = new PoissonDiskSampling(mapa->getWidth(), mapa->getHeight(),mapa);

	int chunksInX = mapa->getWidth() / (CHUNK_SIZE/SQRT2);
	int chunksInY = mapa->getHeight() / (CHUNK_SIZE / SQRT2);
	chunkArray.resize(chunksInX, std::vector<ChunkView*>(chunksInY, nullptr));
	Logger::getInstance() << "koniec";
	Logger::getInstance() << std::endl;

	plant = new Plant();
	plant->setPosition(5100, 5100);
}

void WorldMapView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	mapa->getShader().setParameter("offsetX", mapa->getViewPosition().x);
	mapa->getShader().setParameter("offsetY", mapa->getViewPosition().y);
	mapa->getShader().setParameter("deepWater", 125 / 255.0);
	mapa->getShader().setParameter("shallowWater", 127 / 255.0);
	mapa->getShader().setParameter("sand", 132 / 255.0);
	mapa->getShader().setParameter("time", t);

	//target.draw(*grass);

	target.draw(*waterSprite);
	mapa->getShader().setParameter("sandTexture", *sandTexture);
	//mapa->getShader().setParameter("groundTexture", *groundTexture);
	//mapa->getShader().setParameter("maxValue", 0.51);
	//target.draw(*sandSprite, &mapa->getShader());
	//mapa->getShader().setParameter("minValue", 0.55);
	target.draw(*grassSprite, &mapa->getShader());

//	sf::Vector2f midScreen = mapa->getViewPosition();
	//calculate chunk position
	
	
	sf::Vector2f midScreen = getPosition();
	midScreen.x = midScreen.x + GraphicsOptions::videoMode.width / 2;
	midScreen.y = midScreen.y + GraphicsOptions::videoMode.height / 2;

	//calculate chunk position
	int posX = static_cast<int>(midScreen.x / (CHUNK_SIZE / SQRT2));
	int posY = static_cast<int>(midScreen.y / (CHUNK_SIZE / SQRT2));
	int maxX = static_cast<int> (mapa->getWidth() / (CHUNK_SIZE / SQRT2));
	int maxY = static_cast<int> (mapa->getHeight() / (CHUNK_SIZE / SQRT2));

	for (int x = posX-4; x <= posX + 4; ++x) {
		for (int y = posY-4; y <= posY + 4; ++y) {
			if ((x >= 0) && (x < maxX) && (y >= 0) && (y < maxY)) {
				if (chunkArray[x][y] != nullptr) {
					chunkArray[x][y]->draw(target, states);
				}
			}
		}
	}

	target.draw(*plant, states);
	
	
}

WorldMapView::~WorldMapView() {
	delete mapa;
	delete waterSprite;
	delete sandSprite;
	delete grassSprite;
	delete waterTexture;
	delete sandTexture;
	delete grassTexture;
	delete waterImage;
	delete sandImage;
	delete grassImage;
}

sf::Image WorldMapView::getMapImage() {

	sf::Image img;
	img.create(mapa->getWidth()/10, mapa->getHeight()/10, sf::Color::Black);

	for (int x = 0; x < img.getSize().x; x++) {
		for (int y = 0; y < img.getSize().y; y++) {
			int mapHeight = mapa->getMap(x * 10, y * 10, 0);
			sf::Color mapColor;

			if (mapHeight < 124) {
				mapColor = sf::Color(0, 10, 80 * mapHeight / 255.0);
			}
			else if (mapHeight < 127) {
				mapColor = sf::Color(0, 80, 220 * mapHeight / 255.0);
			}
			else if (mapHeight < 132) {
				mapColor = sf::Color(255 * mapHeight / 255.0, 255 * mapHeight / 255.0, 102 * mapHeight / 255.0);
			}
			else {// if (mapHeight < 180) {
				//	mapColor = sf::Color(178 * mapHeight / 255.0, 255 * mapHeight / 255.0, 102 * mapHeight / 255.0);
				//}
				//else {
				mapColor = sf::Color(0 * mapHeight / 255.0, 102 * mapHeight / 255.0, 0 * mapHeight / 255.0);

			}

			img.setPixel(x, y, mapColor);
		}
	}

	return img;
}

sf::Vector2f WorldMapView::getSpawnPoint() {
	return sf::Vector2f(mapa->getWidth() /3.6f, mapa->getHeight() / 3.6f);
}

void WorldMapView::setViewPosition(sf::Vector2f position) {
	mapa->setViewPosition(position);
}

sf::Vector2f WorldMapView::getViewPosition() {
	return mapa->getViewPosition();
}

sf::Vector2f WorldMapView::getWorldBounds() {
	return sf::Vector2f(mapa->getWidth(), mapa->getHeight());
}

PoissonDiskSampling * WorldMapView::getPoisson (){
	return poisson;
}

void WorldMapView::update() {
	//Logger log = Logger::getInstance();
	sf::Vector2f midScreen = getPosition();
	midScreen.x = midScreen.x + GraphicsOptions::videoMode.width / 2;
	midScreen.y = midScreen.y + GraphicsOptions::videoMode.height / 2;

	//calculate chunk position
	int posX = static_cast<int>(midScreen.x / (CHUNK_SIZE / SQRT2));
	int posY = static_cast<int>(midScreen.y / (CHUNK_SIZE / SQRT2));
	int maxX = static_cast<int> (mapa->getWidth() / (CHUNK_SIZE / SQRT2));
	int maxY = static_cast<int> (mapa->getHeight() / (CHUNK_SIZE / SQRT2));

	//creating chunks
	if (last.x != posX || last.y != posY) {
		last.x = posX;
		last.y = posY;



		for (int x = posX - 5; x <= posX + 5; ++x) {
			for (int y = posY - 5; y <= posY + 5; ++y) {
				// if isn't outside the ma	
				if ((x >= 0) && (x < maxX) && (y >= 0) && (y < maxY)) {
					// if it's not created yet
					if (!chunkArray[x][y]) {
						//create				
						chunkArray[x][y] = new ChunkView();
						chunkArray[x][y]->setObiectArray(poisson->getPositions()[x][y]);
					}
				}

			}
		}

		for (int x = posX - 6; x <= posX + 6; ++x) {
			for (int y = posY - 6; y <= posY + 6; ++y) {
				if ((x >= 0) && (x < maxX) && (y >= 0) && (y < maxY)) {
					if ((abs(x - posX) == 6 || abs(y - posY) == 6)) {
						if (chunkArray[x][y] != nullptr) {
							delete chunkArray[x][y];
							chunkArray[x][y] = nullptr;
							//assert(chunkArray[x][y] != nullptr);
						}
					}
				}
			}
		}

	}
}
