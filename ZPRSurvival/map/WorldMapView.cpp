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

	int width = mapa->getWidth();
	int height = mapa->getHeight();

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
	waterTexture->loadFromImage(*waterImage);
	sandTexture->loadFromImage(*sandImage);
	grassTexture->loadFromImage(*grassImage);
	waterTexture->setRepeated(true);
	sandTexture->setRepeated(true);
	grassTexture->setRepeated(true);
	waterSprite = new Sprite(*waterTexture, sf::IntRect(0, 0, width, height));
	sandSprite = new Sprite(*sandTexture, sf::IntRect(0, 0, width, height));
	grassSprite = new Sprite(*grassTexture, sf::IntRect(0, 0, width, height));
	Logger::getInstance() << "Lets start this shit";
	Logger::getInstance () << std::endl;
	poisson = new PoissonDiskSampling(mapa->getWidth(), mapa->getHeight(),mapa);
	
	//std::vector<sf::Vector2f>& allPoints = poisson->getPositions();
	//Logger::getInstance() << allPoints.size() ;
	//Logger::getInstance() << std::endl;
	/*
	int chunksInX = mapa->getWidth() / 1000;
	int chunksInY = mapa->getHeight() / 1000;
	chunkArray.resize(chunksInX, std::vector<ChunkView*>(chunksInY, nullptr));
	chunkObjectsArray.resize(chunksInX, std::vector<std::vector<sf::Vector2f>>(chunksInY, std::vector<sf::Vector2f>(0)));
	PoissonDiskSampling* poisson;
	poisson = new PoissonDiskSampling(mapa->getWidth(), mapa->getHeight());
	std::vector<sf::Vector2f> allPoints = poisson->getPositions();
	for (auto &iterator : allPoints) {
		int indexX = iterator.x / 100;
		int indexY = iterator.y / 100;
		chunkObjectsArray[indexX][indexY].push_back(iterator);
	}
	*/
}

void WorldMapView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	mapa->getShader().setParameter("offsetX", mapa->getViewPosition().x);
	mapa->getShader().setParameter("offsetY", mapa->getViewPosition().y);
	mapa->getShader().setParameter("deepWater", 125/255.0);
	mapa->getShader().setParameter("shallowWater", 127/255.0);
	mapa->getShader().setParameter("sand", 131/255.0);
	mapa->getShader().setParameter("time", t);

	//target.draw(*grass);

	target.draw(*waterSprite);
	//mapa->getShader().setParameter("minValue", 0.5);
	//mapa->getShader().setParameter("maxValue", 0.51);
	//target.draw(*sandSprite, &mapa->getShader());
	//mapa->getShader().setParameter("minValue", 0.55);
	target.draw(*grassSprite, &mapa->getShader());
	/*
	sf::Vector2f midScreen = mapa->getViewPosition();
	//calculate chunk position
	int posX = static_cast<int>(midScreen.x/100);
	int posY = static_cast<int>(midScreen.y/100);
	//creating chunks
	for (int x = posX - 5; x <= posX + 5; ++x) {
		for (int y = posY - 5; y < posY + 5; ++y) {
			// if isn't outside the map
			if (x>0 && x < static_cast<int> (mapa->getWidth() / 100) && y>0 && y < static_cast<int> (mapa->getHeight() / 100)) {
				// if it's not created yet
				if (!chunkArray[x][y]) {
					//create
					chunkArray[x][y] = new ChunkView();
					chunkArray[x][y]->setObiectArray(chunkObjectsArray[x][y]);
				}
			}	

		}

	}
	*/
	/*for (int x = posX - 3; x <= posX + 3; ++x) {
		for (int y = posY - 3; y < posY + 3; ++y) {
		
			chunkArray[x][y]->draw();
		
		}
	}*/



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
	img.create(mapa->getWidth(), mapa->getHeight(), sf::Color::Black);

	for (int x = 0; x < img.getSize().x; x++) {
		for (int y = 0; y < img.getSize().y; y++) {
			int mapHeight = mapa->getMap(x, y, 0);
			sf::Color mapColor;

			if (mapHeight < 124) {
				mapColor = sf::Color(0, 10, 80 * mapHeight / 255.0);
			}
			else if (mapHeight < 127) {
				mapColor = sf::Color(0, 80, 220 * mapHeight / 255.0);
			}
			else if (mapHeight < 131) {
				mapColor = sf::Color(255 * mapHeight / 255.0, 255 * mapHeight / 255.0, 102 * mapHeight / 255.0);
			}
			else if (mapHeight < 180) {
				mapColor = sf::Color(178 * mapHeight / 255.0, 255 * mapHeight / 255.0, 102 * mapHeight / 255.0);
			}
			else {
				mapColor = sf::Color(0 * mapHeight / 255.0, 102 * mapHeight / 255.0, 0 * mapHeight / 255.0);

			}

			img.setPixel(x, y, mapColor);
		}
	}

	return img;
}

sf::Vector2f WorldMapView::getSpawnPoint() {
	return sf::Vector2f(mapa->getWidth() /3.5f, mapa->getHeight() / 3.5f);
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

void WorldMapView::update() {
	//Logger log = Logger::getInstance();
	sf::Vector2f midScreen = getPosition();
	midScreen.x = midScreen.x + GraphicsOptions::videoMode.width / 2;
	midScreen.y = midScreen.y + GraphicsOptions::videoMode.height / 2;

	//calculate chunk position
	int posX = static_cast<int>(midScreen.x / 100);
	int posY = static_cast<int>(midScreen.y / 100);
	int maxX = static_cast<int> (mapa->getWidth() / 100);
	int maxY = 20;
	//log << "position - x:";
	//log << posX;
	//log << " y:";
	//log << posY;
	//log << std::endl;

	//creating chunks
	if (last.x != posX || last.y != posY) {
		last.x = posX;
		last.y = posY;

		for (int x = posX - 1; x <= posX + 1; ++x) {
			for (int y = posY - 1; y <= posY + 1; ++y) {
				// if isn't outside the map
				if ((x >= 0) && (x < maxX) && (y >= 0) && (y < maxY)) {
					// if it's not created yet
					if (!chunkArray[x][y]) {
						//create
						chunkArray[x][y] = new ChunkView();
						chunkArray[x][y]->setObiectArray(chunkObjectsArray[x][y]);
						Logger::getInstance() << std::endl;
						Logger::getInstance() << "midx" << midScreen.x <<" midy "<< midScreen.y;
						Logger::getInstance() << std::endl;
						Logger::getInstance() << " max x " << maxX << "max y" << maxY;
						Logger::getInstance() << "created chunk - x:";
						Logger::getInstance() << x;
						Logger::getInstance() << " y:";
						Logger::getInstance() << y;
						Logger::getInstance() << std::endl;
					}
				}

			}
		}
	}

}
