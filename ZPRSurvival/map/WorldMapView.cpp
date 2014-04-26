#include "WorldMapView.h"


WorldMapView::WorldMapView() {
	mapa = new WorldMap();

	int width = mapa->getWidth();
	int height = mapa->getHeight();

	t = 0.0f;

	// = new sf::RenderTexture();
	image = new sf::Image();
	texture = new sf::Texture();
	blank = new sf::Texture();
	image->create(static_cast<float>(GraphicsOptions::videoMode.width), static_cast<float>(GraphicsOptions::videoMode.height), sf::Color::Blue);
	//image->loadFromFile("./resources/textures/background/grassx.png");
	texture->loadFromImage(*image);
	texture->setRepeated(true);
	blank->create(width, height);
	setTexture(*blank);
	grass = new Sprite(*texture, sf::IntRect(0,0,width,height));
	//creating table of chunks
	int chunksVer = mapa->getHeight() / 100;
	int chunksHor = mapa->getWidth() / 100;
	chunks.resize(chunksHor, std::vector<ChunkView*>(chunksVer,nullptr));
	

	poisson = new PoissonDiskSampling(mapa->getWidth(), mapa->getHeight());
	std::vector<sf::Vector2f> coordinates = poisson->getPositions();
	for (auto& iterator : coordinates) {
		sf::CircleShape circle;
		circle.setPosition(iterator);
		circle.setOutlineColor(sf::Color::Red);
		circle.setRadius(25);
		circle.setFillColor(sf::Color::Cyan);
		mapContent.push_back(circle);
	}


}

void WorldMapView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	mapa->getShader().setParameter("offsetX", mapa->getViewPosition().x);
	mapa->getShader().setParameter("offsetY", mapa->getViewPosition().y);
	
	//target.draw(*grass);
	target.draw(*grass, &mapa->getShader());
	for (auto& iterator : mapContent) {
		//target.draw(iterator);
	}
}

WorldMapView::~WorldMapView() {
	delete mapa;
	delete texture;
	delete image;
}

sf::Image WorldMapView::getMapImage() {

	sf::Image img;
	img.create(WIDTH, HEIGHT, sf::Color::Black);

	for (int x = 0; x < img.getSize().x; x++) {
		for (int y = 0; y < img.getSize().y; y++) {
			int mapHeight = mapa->getMap(x, y, 0);
			sf::Color mapColor;

			if (mapHeight < 117) {
				mapColor = sf::Color(0, 10, 80 * mapHeight / 255.0);
			}
			else if (mapHeight < 127) {
				mapColor = sf::Color(0, 80, 220 * mapHeight / 255.0);
			}
			else if (mapHeight < 135) {
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
	return sf::Vector2f(mapa->getWidth() /2.0f, mapa->getHeight() / 2.0f);
}

void WorldMapView::setViewPosition(sf::Vector2f position) {
	mapa->setViewPosition(position);
}

sf::Vector2f WorldMapView::getWorldBounds() {
	return sf::Vector2f(mapa->getWidth(), mapa->getHeight());
}