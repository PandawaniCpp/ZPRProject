#include "WorldMapView.h"


WorldMapView::WorldMapView() {
	mapa = new WorldMap();

	int width = mapa->getWidth();
	int height = mapa->getHeight();

	t = 0.0f;

	// = new sf::RenderTexture();
	image = new sf::Image();
	image->create(static_cast<float>(GraphicsOptions::videoMode.width), static_cast<float>(GraphicsOptions::videoMode.height), sf::Color::Blue);
	texture = new Texture();
	texture->create(width, height);

	texture->loadFromImage(*image);
	setTexture(*texture);
}

void WorldMapView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	mapa->getShader().setParameter("offsetX", t);
	target.draw((Sprite)*this, &mapa->getShader());
}

WorldMapView::~WorldMapView() {
	delete mapa;
	delete texture;
	delete image;
}

sf::Image WorldMapView::getMapImage() {

	sf::Image img;
	img.create(1000, 1000, sf::Color::Black);

	for (int x = 0; x < img.getSize().x; x++) {
		for (int y = 0; y < img.getSize().y; y++) {
			img.setPixel(x, y, sf::Color(mapa->getMap(x, y, 0), mapa->getMap(x, y, 0), mapa->getMap(x, y, 0)));
		}
	}

	return img;
}

sf::Vector2f WorldMapView::getSpawnPoint() {
	return sf::Vector2f(mapa->getWidth(), mapa->getHeight());
}