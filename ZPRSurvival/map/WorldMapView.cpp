#include "WorldMapView.h"


WorldMapView::WorldMapView() {
	mapa = new WorldMap();
	t = 0.0f;
	// = new sf::RenderTexture();
	initialize();
}

WorldMapView::WorldMapView(int seed, double persistence, double zoom, int octaves, int width, int height) {
	mapa = new WorldMap(seed, persistence, zoom, octaves, width, height);
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

}

void WorldMapView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	mapa->getShader().setParameter("offsetX", mapa->getViewPosition().x);
	mapa->getShader().setParameter("offsetY", mapa->getViewPosition().y);
	mapa->getShader().setParameter("deepWater", 117/255.0);
	mapa->getShader().setParameter("shallowWater", 127/255.0);
	mapa->getShader().setParameter("sand", 135/255.0);
	//target.draw(*grass);

	target.draw(*waterSprite);
	//mapa->getShader().setParameter("minValue", 0.5);
	//mapa->getShader().setParameter("maxValue", 0.51);
	//target.draw(*sandSprite, &mapa->getShader());
	//mapa->getShader().setParameter("minValue", 0.55);
	target.draw(*grassSprite, &mapa->getShader());
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

sf::Vector2f WorldMapView::getViewPosition() {
	return mapa->getViewPosition();
}

sf::Vector2f WorldMapView::getWorldBounds() {
	return sf::Vector2f(mapa->getWidth(), mapa->getHeight());
}