#include "WorldMapView.h"


WorldMapView::WorldMapView() {
	mapa = new WorldMap();

	int width = mapa->getWidth();
	int height = mapa->getHeight();

	t = 0.0f;

	// = new sf::RenderTexture();
	image = new sf::Image();
	image->create(700, 700, sf::Color::Blue);
	texture = new Texture();
	texture->create(width, height);

	texture->loadFromImage(*image);
	setTexture(*texture);
}

void WorldMapView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	mapa->getShader().setParameter("time", t);
	target.draw((Sprite)*this, &mapa->getShader());
}

WorldMapView::~WorldMapView() {
	delete mapa;
	delete texture;
	delete image;
}